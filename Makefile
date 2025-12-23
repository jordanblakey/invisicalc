VENV_DIR = venv
PYTHON = $(VENV_DIR)/bin/python
PIP = $(VENV_DIR)/bin/pip
PYINSTALLER = $(VENV_DIR)/bin/pyinstaller
APP_NAME = Calculator
SCRIPT = calculator.py

.PHONY: all build run clean install

all: build

$(VENV_DIR):
	python3 -m venv --system-site-packages $(VENV_DIR)
	$(PIP) install pyinstaller

install: $(VENV_DIR)

build: install
	$(PYINSTALLER) --onefile --windowed --name "$(APP_NAME)" --add-data "style.css:." $(SCRIPT)

run:
	python3 $(SCRIPT)

clean:
	rm -rf build dist $(APP_NAME).spec
	rm -rf __pycache__
