# qt-medialib
A personal multimedia library built using the Qt6 Framework

### Requirements:
- qmake 3.1
- Qt6

### Build
`qmake` to generate the Makefile and `make` to start the build process, the compiled application can be found in `bin/`

### Run
From the root project directory run `./bin/medialib`
The executable itself can be moved anywhere in the filesystem and work fine.
A common place on Linux is `/usr/local/bin`, so it's directly accessible in the user shell

### Usage
The user can add various media types to the collection by clicking on the add button in the menu bar, right now only Movies, Books and Videogames are supported.
When adding media the details view opens up making it possible for the user to edit the media's metadata by filling fields such as the name of the media, the release date and even the banner image to display in the home page
Created media can be later edited or even deleted.
The search bar provides basic filtering abilities to isolate specific media types and search in all the fields possible.
Data is persistent and is saved in a `data/` folder in the default location of your OS, for instance on Linux the default path is `/home/user/.config/medialib/data`.
Data can be exported or imported from the filesystem via an interactive dialog.
> Note: to correctly import data, import the `data/` folder itself, not items from the subdirectories such as `images/` or the `data.json`, this is crucial.
