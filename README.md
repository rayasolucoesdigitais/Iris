## Iris
**Iris** is a powerful and fast **image viewer engine** for Linux. It supports popular image formats like PNG, JPG, JPEG, WebP, BMP, GIF, TIF and TIFF.

## Features

- View **multiple images**
- Zoom in and out using **keyboard** (`+` / `-`) or **mouse wheel**
- Pan images with the **mouse**
- **Auto-fit** image to window on load
- Lightweight and fast

## Installation
1. **Clone the repository:**
```bash
git clone https://github.com/s-r-e-e-r-a-j/Iris.git
```
2. **Go to the Iris directory:**
```bash
cd Iris
```
3. **Give execute permission to the `install.sh` script:**
```bash
chmod +x install.sh
```
4. **Run the install script:**
```bash
./install.sh
```
This will:
- Install required dependencies (`SDL2`, `SDL2_image`, compiler tools)
- Build Iris using `make`
- Copy the binary to `/usr/local/bin`

## Usage
```bash
iris image1.jpg image2.png
```
- Use **Right/Left arrows** to switch images
- Use `+` / `-` **keys** or **mouse wheel** to zoom
- Click and drag with **left mouse button to pan**

## Uninstall
To remove Iris:
```bash
chmod +x uninstall.sh && ./uninstall.sh
```
## License
This project is licensed under the GNU General Public License v3.0
