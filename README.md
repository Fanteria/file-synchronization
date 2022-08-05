# File synchronization

This program periodically synchronizes the source folder with the replica folder. Synchronization is one way, so the program can remove redundant files or folders from the replica folder.

# Usage

Run `file-synchronization SOURCE REPLICA [OPTION] ...` where `SOURCE` is a path to the source directory and `REPLICA` is a path to the replica directory. Possible options are in the table below.

| short |     full     | description                                    |
| :---: | :----------: | :--------------------------------------------- |
| `-i`  | `--interval` | Positive integer of iteration time in seconds. |
| `-l`  |   `--log`    | Name of file for logging.                      |
