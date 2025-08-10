# Elite--FAP_subghz_tools-FLIPPER_ZERO
Remastered Elite version---TNT Professional tools>>>>FAP

4
____________________________________________________________________________________________________________________________________________________


# How to Add RocketGod Sub-GHz Toolkit FAP to Your Flipper Firmware





- **Set up the Flipper Zero toolchain** on your computer (Windows, Mac, Linux).
  - [Official setup instructions](https://flipperzero.one/developers/)
  - Make sure you can build and flash custom apps (`fbt fap` command should work).



## 2. Get the App Source Files

- Download or clone the source files for the RocketGod FAP app:
  - `rocketgod_subghz_toolkit.c` (main app code)
  - `manifest.txt` (app metadata)
  - (Optional) `icon.png` (app icon)
  - `README.md` (instructions)

- Place these files in a new folder inside your Flipper firmware's `applications_user` directory.


  flipperzero-firmware/
  └── applications_user/
      └── rocketgod-subghz-toolkit/
          ├── rocketgod_subghz_toolkit.c
          ├── manifest.txt
          ├── icon.png
          └── README.md

- On your Flipper Zero SD card, create the folder:
 
  /ext/apps_data/rocketgod-subghz-toolkit/subghz/

- Download `.sub` scripts from [rocketgod-subghz-toolkit GitHub](https://github.com/rocketgod-subghz-toolkit).
- Optionally, organize scripts into categories by creating subfolders (e.g., `/brands`, `/protocols`).
- Place all scripts and folders inside `/subghz/`.

  /ext/apps_data/rocketgod-subghz-toolkit/subghz/
  ├── garage.sub
  ├── cars.sub
  ├── brands/
  │   ├── ford.sub
  │   └── toyota.sub
  └── protocols/
      ├── keeloq.sub
      └── pt2262.sub
 Build the App

- **Open a terminal** in your firmware folder.
- Run:
 
  fbt fap

- After building, find the `.fap` file in `dist/apps/` (or similar build output folder).

 Install the App on Flipper Zero

- **Copy the built `.fap` file** to your Flipper Zero SD card at:

  /apps/
  Using the App (Step-by-Step)

1. **On Flipper Zero**, navigate to the "Apps" menu.
2. **Open "RocketGod Sub-GHz Toolkit"**.
3. The app automatically scans `/subghz/` and detects:
    - All `.sub` scripts.
    - Any subfolders as "Categories" (e.g., brand, protocol, etc.).
4. **Browse scripts:**
    - Use navigation buttons to scroll through scripts.
    - Use category selection to filter scripts.
    - Use search to type and filter by script name.
5. **View script info:**
    - Select a script to see its name, size, last modified date, category, and location.
6. **Run a script:**
    - Press OK/Run to execute the selected Sub-GHz script using Flipper's hardware.
    - The script is instantly transmitted.

7. **Exit or keep browsing:**
    - Press BACK to exit the app.
    - You can add/remove scripts on SD card anytime—app will auto-detect changes on next launch.

 How It Works

- The app auto-discovers all `.sub` files and organizes them by category/folder.
- You get a menu with:
    - Category selection
    - Search/filter option
    - Script info display
- Scripts can be added, removed, or organized at any time—just edit the SD card.
- No need to recompile the app for new scripts or folders.


## Support Resources

- [RocketGod Sub-GHz Toolkit repo](https://github.com/rocketgod-subghz-toolkit)
- [Flipper Zero developer docs](https://flipperzero.one/developers/)

