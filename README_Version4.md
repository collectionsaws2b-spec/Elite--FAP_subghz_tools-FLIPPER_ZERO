# RocketGod Sub-GHz Toolkit FAP (Advanced)

## Features

- **Auto-packages all scripts:** Just copy `.sub` files into `/ext/apps_data/rocketgod-subghz-toolkit/subghz` on your SD card.
- **Categories:** Subfolders become categories (brand, protocol, etc).
- **Search/filter:** Type to search scripts by name.
- **Script info:** See details (filename, size, modified date, category).
- **Instant execution:** Select and run scripts in a tap.
- **No restrictions:** Add, remove, organize scripts however you want.

---

## Installation

1. **Set up Flipper Zero dev environment:**  
   [Flipper Zero Developer Docs](https://flipperzero.one/developers/)

2. **Create app folder & files:**  
   - Place `rocketgod_subghz_toolkit.c` and `manifest.txt` in your app source folder.
   - Add `icon.png` (optional).

3. **Download scripts:**  
   From [rocketgod-subghz-toolkit](https://github.com/rocketgod-subghz-toolkit), copy `.sub` files and any desired subfolders to `/ext/apps_data/rocketgod-subghz-toolkit/subghz` on your Flipper SD card.

4. **Build the FAP:**  
   ```
   fbt fap
   ```
   The `.fap` will be in your `dist` folder.

5. **Install on Flipper:**  
   - Copy the `.fap` file to `/apps/` on your Flipper SD card.
   - Ensure your script folder structure is present.

---

## Usage

- **Start the app** from Flipper’s menu.
- **Browse by category**, or search for scripts.
- **Select a script** to see details and run instantly.
- **Add/remove scripts at any time**—just copy files, no rebuild needed.

---

## Example Folder Structure

```plaintext
/ext/apps_data/rocketgod-subghz-toolkit/subghz/
├── garage.sub
├── cars.sub
├── alarm.sub
├── brands/
│   ├── ford.sub
│   ├── toyota.sub
│   └── vw.sub
└── protocols/
    ├── keeloq.sub
    └── pt2262.sub
```

---

## Extending

- Add more categories: Just make folders inside `subghz/`.
- Add more scripts: Copy `.sub` files—app finds them automatically.
- UI: You can further enhance menu navigation, add favorites, etc.

---

## Troubleshooting

- **Scripts not listed?** Make sure they have `.sub` extension and are in the right folder.
- **App not visible?** Ensure `.fap` is in `/apps/` and manifest is correct.

---

## Support

- [RocketGod toolkit repo](https://github.com/rocketgod-subghz-toolkit)
- [Flipper Zero developer docs](https://flipperzero.one/developers/)