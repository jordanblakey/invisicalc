# invisicalc

A description of this project.

## Build System

```txt
requires blueprint-compiler to build .blp to .ui files.
this must be configured in meson.build
sudo apt install blueprint-compiler

# deb build tools - are these needed?
sudo apt update
sudo apt install build-essential debhelper dh-make devscripts

sudo apt update
sudo apt install git-buildpackage quilt
dh_make --createorig -s
dch --create -v 0.1.0 --package invisicalc "Initial release."
git tag v0.1.0

# Run each time
dch --increment
gbp buildpackage -us -uc --git-ignore-branch
sudo apt --reinstall install ./invisicalc_0.1.0-X_amd64.deb

# dpkg-source --commit # use a patch name like 
# Use this when the main 'gbp buildpackage' command fails with "aborting due to unexpected upstream changes" error.

# Check the existing patches like
# quilt series
# debian/patches/0001-add-manpage.patch
# debian/patches/0002-update-manpage.patch


```


Phase 1: Development and Version Control (GNOME Builder / Git)
You use GNOME Builder as your IDE and Git as your primary version control system.
Tools: git, GNOME Builder IDE
Purpose: Write source code (.c, meson.build) and track development history using git commit.
Output: A working application compiled natively by Meson and Ninja.
Phase 2: Debian Packaging Configuration (Metadata & Tools)
You set up a separate layer of metadata to instruct Debian tools how to build your package.
Tools: apt install (for debhelper, gbp, quilt), text editor (for config files)
Key Files Created:
debian/control: Package name, description, and dependencies.
debian/rules: The "makefile" that defines the build process using --buildsystem=meson.
debian/changelog: Tracks the package version history.
debian/patches/ & debian/source/format: The Quilt version control system for packaging-specific changes (like adding a manpage).
Phase 3: Iterative Building and Packaging (gbp Workflow)
Once configured, you use a three-step terminal workflow every time you update your application:
Step	Action	Tool Used
1.	Increment version number in changelog.	dch --increment
2.	Build the source and binary .deb package.	gbp buildpackage -us -uc
3.	(Optional) Install/reinstall the local .deb.	sudo apt --reinstall install
This process efficiently converts your source code into a compliant, shareable .deb installer file located in your project's parent directory.
Do you have any final questions about this process before you continue developing your application?



