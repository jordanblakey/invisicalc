
# Invisicalc

Invisicalc is a lightning-fast, NumPad-centric calculator designed for rapid basic arithmetic. Think of it as a dedicated visual extension of your keyboard's NumPad—unobtrusive, immediate, and purely functional. Built with C, GTK 4, and Libadwaita for a modern, native GNOME experience.

## Features

- **Standard Calculator Functions**: Add, subtract, multiply, divide, exponents and parentheses.
- **Modern UI**: Uses Libadwaita for a sleek, adaptive interface that fits perfectly on the GNOME desktop.
- **Keyboard Support**: Full support for numpad and standard keyboard numbers/operators.
- **Desktop Integration**: Includes a proper application icon and dock integration.
- **Blueprint Layouts**: The UI is defined using `.blp` blueprint files for concise and readable layout definitions.
- **Custom Styling**: Styled with CSS for a polished look.

## Shortcuts

- `Enter` / `Numpad Enter` / `=`: Calculate result
- `Backspace`: Delete last character
- `Escape` / `c` / `C`: Clear display
- `Ctrl+Q` or `Ctrl+W`: Quit application

## Prerequisites

To build Invisicalc, you need the following dependencies:

- `meson` (>= 1.0.0)
- `ninja-build`
- `pkg-config`
- `libgtk-4-dev`
- `libadwaita-1-dev` (>= 1.4)
- `blueprint-compiler`

For Debian/Ubuntu packaging tools:
- `build-essential`
- `debhelper`
- `dh-make`
- `git-buildpackage`
- `devscripts`

## Building from Source

You can build the application using the Meson build system.

### Quick Start (Development)

To quickly compile and run the application locally:

```bash
make run
```

### Manual Build Instructions

```bash
# Setup the build directory
meson setup build

# Compile the application
meson compile -C build

# Run the application (without installing)
./build/src/invisicalc
```

## Debian Packaging

This project includes a `Makefile` to simplify the Debian packaging workflow. It uses `git-buildpackage` (gbp) to manage builds.

### Commands

- **Build Package**: Increments the version, commits the change, and builds the `.deb` package.
  ```bash
  make deb
  ```
  The resulting artifacts will be placed in the `deb-build/` directory.

- **Install Package**: Installs the newly built package.
  ```bash
  make install
  ```

- **Clean**: Removes build artifacts.
  ```bash
  make clean
  ```

### Manual Packaging Workflow

If you prefer running the commands manually:

1.  **Increment Version**:
    ```bash
    dch --increment "Your change message"
    git add debian/changelog && git commit -m "Bump version"
    ```

2.  **Build**:
    ```bash
    mkdir -p deb-build
    # Ensure source tarball exists if needed, or rely on git tag/branch
    gbp buildpackage -us -uc --git-ignore-branch --git-export-dir=deb-build
    ```

## Project Structure

- `src/`: Source code.
    - `main.blp`: The main window layout definition (Blueprint).
    - `main.css`: Application-wide CSS styling.
    - `invisicalc-*.c/h`: C source files for application logic and window management.
- `data/`: Desktop files, icons, and GSettings schemas.
- `debian/`: Debian packaging metadata (control, rules, changelog).
- `po/`: Translations.

## Development Notes

- **CSS**: Styles are loaded from `src/main.css`.
- **Blueprints**: The `blueprint-compiler` is used to compile `.blp` files into XML `.ui` files during the build process.
- **Resources**: The application uses `GResource` to embed the UI and CSS files into the binary.

```txt
dpkg -L invisicalc

```