#include <furi.h>
#include <gui/gui.h>
#include <storage/storage.h>
#include <lib/subghz/subghz.h>
#include <lib/subghz/subghz_file.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define SCRIPT_ROOT "/ext/apps_data/rocketgod-subghz-toolkit/subghz"

typedef struct {
    char* name;
    char* path;
    size_t size;
    time_t mtime;
    char* category;
} ScriptEntry;

typedef struct {
    ScriptEntry* entries;
    size_t count;
    size_t capacity;
} ScriptList;

static void script_list_init(ScriptList* list) {
    list->entries = NULL;
    list->count = 0;
    list->capacity = 0;
}

static void script_list_add(ScriptList* list, const char* name, const char* path, size_t size, time_t mtime, const char* category) {
    if(list->count == list->capacity) {
        list->capacity = (list->capacity == 0) ? 16 : list->capacity * 2;
        list->entries = realloc(list->entries, sizeof(ScriptEntry) * list->capacity);
    }
    list->entries[list->count].name = strdup(name);
    list->entries[list->count].path = strdup(path);
    list->entries[list->count].size = size;
    list->entries[list->count].mtime = mtime;
    list->entries[list->count].category = category ? strdup(category) : NULL;
    list->count++;
}

static void script_list_free(ScriptList* list) {
    for(size_t i = 0; i < list->count; i++) {
        free(list->entries[i].name);
        free(list->entries[i].path);
        if(list->entries[i].category) free(list->entries[i].category);
    }
    free(list->entries);
}

static void scan_scripts(ScriptList* list) {
    DIR* dir = opendir(SCRIPT_ROOT);
    if(!dir) return;
    struct dirent* entry;
    while((entry = readdir(dir))) {
        if(entry->d_type == DT_DIR && strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            // Category folder
            char cat_path[256];
            snprintf(cat_path, sizeof(cat_path), "%s/%s", SCRIPT_ROOT, entry->d_name);
            DIR* cat_dir = opendir(cat_path);
            struct dirent* script;
            while(cat_dir && (script = readdir(cat_dir))) {
                if(script->d_type == DT_REG && strstr(script->d_name, ".sub")) {
                    char script_path[256];
                    snprintf(script_path, sizeof(script_path), "%s/%s", cat_path, script->d_name);
                    struct stat st;
                    if(stat(script_path, &st) == 0)
                        script_list_add(list, script->d_name, script_path, st.st_size, st.st_mtime, entry->d_name);
                }
            }
            if(cat_dir) closedir(cat_dir);
        } else if(entry->d_type == DT_REG && strstr(entry->d_name, ".sub")) {
            // Top-level script
            char script_path[256];
            snprintf(script_path, sizeof(script_path), "%s/%s", SCRIPT_ROOT, entry->d_name);
            struct stat st;
            if(stat(script_path, &st) == 0)
                script_list_add(list, entry->d_name, script_path, st.st_size, st.st_mtime, NULL);
        }
    }
    closedir(dir);
}

static void filter_scripts(const ScriptList* src, ScriptList* dst, const char* category, const char* search) {
    script_list_init(dst);
    for(size_t i = 0; i < src->count; i++) {
        int match_cat = category ? (src->entries[i].category && strcmp(src->entries[i].category, category)==0) : 1;
        int match_search = search && strlen(search) ? (strcasestr(src->entries[i].name, search) != NULL) : 1;
        if(match_cat && match_search)
            script_list_add(dst, src->entries[i].name, src->entries[i].path, src->entries[i].size, src->entries[i].mtime, src->entries[i].category);
    }
}

static void list_categories(const ScriptList* list, char*** cats, size_t* cat_count) {
    *cats = NULL;
    *cat_count = 0;
    for(size_t i = 0; i < list->count; i++) {
        if(list->entries[i].category) {
            int found = 0;
            for(size_t j = 0; j < *cat_count; j++)
                if(strcmp((*cats)[j], list->entries[i].category)==0) found = 1;
            if(!found) {
                *cats = realloc(*cats, sizeof(char*) * (*cat_count + 1));
                (*cats)[*cat_count] = strdup(list->entries[i].category);
                (*cat_count)++;
            }
        }
    }
}

static void free_categories(char** cats, size_t cat_count) {
    for(size_t i = 0; i < cat_count; i++) free(cats[i]);
    free(cats);
}

// Replace with actual Flipper UI API (pseudo-code here)
static size_t show_menu(const ScriptList* list, const char* search) {
    // Display menu and return index of selected script, or SIZE_MAX if cancelled
    // Implement: show categories, allow search, show info on selection
    size_t selected = 0;
    // ... pseudo-UI code ...
    return selected;
}

static void show_script_info(const ScriptEntry* entry) {
    char buf[128];
    snprintf(buf, sizeof(buf),
        "Name: %s\nSize: %lu bytes\nModified: %lu\nCategory: %s\nPath: %s",
        entry->name, entry->size, (unsigned long)entry->mtime,
        entry->category ? entry->category : "None", entry->path);
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_popup(gui, buf, 3000);
    furi_record_close(RECORD_GUI);
}

static void run_script(const char* path) {
    SubGhz* subghz = furi_record_open(RECORD_SUBGHZ);
    subghz_file_run(subghz, path);
    furi_record_close(RECORD_SUBGHZ);
}

int32_t rocketgod_subghz_toolkit_app(void* p) {
    ScriptList all_scripts;
    script_list_init(&all_scripts);
    scan_scripts(&all_scripts);

    if(all_scripts.count == 0) {
        Gui* gui = furi_record_open(RECORD_GUI);
        gui_popup(gui, "No .sub scripts found!\nAdd files to /ext/apps_data/rocketgod-subghz-toolkit/subghz", 2500);
        furi_record_close(RECORD_GUI);
        script_list_free(&all_scripts);
        return 0;
    }

    // Discover categories
    char** categories = NULL;
    size_t cat_count = 0;
    list_categories(&all_scripts, &categories, &cat_count);

    // User interaction loop
    char search[64] = {0};
    char* selected_cat = NULL;
    size_t selected_script = SIZE_MAX;
    int running = 1;
    while(running) {
        ScriptList filtered;
        filter_scripts(&all_scripts, &filtered, selected_cat, search);

        selected_script = show_menu(&filtered, search);

        if(selected_script == SIZE_MAX) {
            running = 0; // User cancelled/exit
        } else {
            // Show info and option to run
            show_script_info(&filtered.entries[selected_script]);
            // ... prompt user: Run/Back/Search/Category ...
            // If user selects Run:
            run_script(filtered.entries[selected_script].path);
            // ... option to keep running or exit ...
        }
        script_list_free(&filtered);
    }

    free_categories(categories, cat_count);
    script_list_free(&all_scripts);
    return 0;
}