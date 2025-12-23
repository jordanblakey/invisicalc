APP_NAME = invisicalc
APP_ID = org.jordanblakey.invisicalc.v1
SCRIPT = calculator.py

VENV_DIR = venv
PYTHON = $(VENV_DIR)/bin/python
PIP = $(VENV_DIR)/bin/pip

.PHONY: all build run clean deb

all: run

$(VENV_DIR):
	python3 -m venv --system-site-packages $(VENV_DIR)

# Run locally using venv
run: $(VENV_DIR)
	$(PYTHON) $(SCRIPT)

clean:
	rm -rf build dist deb_dist
	rm -rf __pycache__
	rm -rf $(VENV_DIR)
	rm -rf *.deb

# Native Debian Package Build
deb:
	rm -rf deb_dist
	mkdir -p deb_dist/DEBIAN
	mkdir -p deb_dist/usr/bin
	mkdir -p deb_dist/usr/share/$(APP_NAME)
	mkdir -p deb_dist/usr/share/applications
	mkdir -p deb_dist/usr/share/icons/hicolor/scalable/apps
	
	# Copy Application Files
	cp $(SCRIPT) deb_dist/usr/share/$(APP_NAME)/$(SCRIPT)
	cp style.css deb_dist/usr/share/$(APP_NAME)/style.css
	cp invisicalc_icon.svg deb_dist/usr/share/icons/hicolor/scalable/apps/invisicalc_icon.svg
	
	# Create Launcher Script
	echo "#!/bin/sh" > deb_dist/usr/bin/$(APP_NAME)
	echo "exec python3 /usr/share/$(APP_NAME)/$(SCRIPT) \"\$$@\"" >> deb_dist/usr/bin/$(APP_NAME)
	chmod 755 deb_dist/usr/bin/$(APP_NAME)
	
	# Desktop Entry
	echo "[Desktop Entry]" > deb_dist/usr/share/applications/$(APP_ID).desktop
	echo "Name=$(APP_NAME)" >> deb_dist/usr/share/applications/$(APP_ID).desktop
	echo "Comment=Python GTK Calculator" >> deb_dist/usr/share/applications/$(APP_ID).desktop
	echo "Exec=/usr/bin/$(APP_NAME)" >> deb_dist/usr/share/applications/$(APP_ID).desktop
	echo "Icon=invisicalc_icon" >> deb_dist/usr/share/applications/$(APP_ID).desktop
	echo "Type=Application" >> deb_dist/usr/share/applications/$(APP_ID).desktop
	echo "Categories=Utility;Calculator;" >> deb_dist/usr/share/applications/$(APP_ID).desktop
	echo "Terminal=false" >> deb_dist/usr/share/applications/$(APP_ID).desktop
	echo "StartupNotify=true" >> deb_dist/usr/share/applications/$(APP_ID).desktop
	
	# Debian Control File
	echo "Package: invisicalc" > deb_dist/DEBIAN/control
	echo "Version: 1.0.0" >> deb_dist/DEBIAN/control
	echo "Section: utils" >> deb_dist/DEBIAN/control
	echo "Priority: optional" >> deb_dist/DEBIAN/control
	echo "Architecture: all" >> deb_dist/DEBIAN/control
	echo "Depends: python3, python3-gi, gir1.2-gtk-4.0" >> deb_dist/DEBIAN/control
	echo "Installed-Size: $$(du -s deb_dist/usr | cut -f1)" >> deb_dist/DEBIAN/control
	echo "Maintainer: Jordan Blakey" >> deb_dist/DEBIAN/control
	echo "License: MIT" >> deb_dist/DEBIAN/control
	echo "Homepage: https://github.com/jordanblakey/invisicalc" >> deb_dist/DEBIAN/control
	echo "Description: A minimal, invisible-style calculator" >> deb_dist/DEBIAN/control
	echo " A sleek, keyboard-friendly calculator application for Gnome built with Python and GTK4." >> deb_dist/DEBIAN/control
	echo " Designed to be unobtrusive and aesthetically pleasing, it features a NumPad-first design, proper desktop integration, and a clean interface." >> deb_dist/DEBIAN/control
	
	# Build Package
	dpkg-deb --root-owner-group --build deb_dist invisicalc.deb
	rm -rf deb_dist
