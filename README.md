# Invisicalc 83

A sleek, keyboard-friendly calculator application built with Python and GTK4.

## Features

-   **Standard Calculator Functions**: Add, subtract, multiply, divide.
-   **Keyboard Support**: Full support for numpad and standard keyboard numbers/operators.
-   **Desktop Integration**: Includes a proper application icon and dock integration.
-   **Shortcuts**:
    -   `Enter` / `Numpad Enter` / `=`: Calculate result
    -   `Backspace`: Delete last character
    -   `Escape` / `c` / `C`: Clear display
    -   `Ctrl+Q` or `Ctrl+W`: Quit application

## Installation

### Option 1: Debian Package (Recommended)

This creates a standard system package that is easy to install and remove.

1.  **Build the package**:
    ```bash
    make deb
    ```
2.  **Install**:
    ```bash
    sudo dpkg -i invisicalc.deb
    ```


## Uninstallation

### If installed via Debian Package (.deb)

```bash
sudo apt remove invisicalc
```



## Development

-   **Run locally**: `make run`
-   **Clean build artifacts**: `make clean`

## License

MIT

