OUTPUT_DIR = deb-build

.PHONY: all deb install run clean

all: deb

deb:
	@echo "Incrementing version..."
	dch --increment "Build via Makefile"
	@echo "Committing version bump..."
	git add debian/changelog
	git commit -m "Bump version for build"
	@echo "Building package..."
	mkdir -p $(OUTPUT_DIR)
	gbp buildpackage -us -uc --git-ignore-branch --git-export-dir=$(OUTPUT_DIR)
	@echo "Build complete. Files are in $(OUTPUT_DIR)/"

install:
	@echo "Installing package..."
	sudo apt install --reinstall ./$(OUTPUT_DIR)/*.deb

run:
	@if [ ! -d "build" ]; then meson setup build; fi
	meson compile -C build
	./build/src/invisicalc

clean:
	rm -rf $(OUTPUT_DIR)

