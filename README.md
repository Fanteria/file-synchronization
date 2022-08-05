# File synchronization

This program periodically synchronize source folder with replica folder. Synchronization is one way, so program can remove redundant files or folders from replica folder.

# Usage

Run `file-synchronization SOURCE REPLICA [OPTION] ...` where `SOURCE` is path to source directory and `REPLICA` is path to replica directory. Possible options are in table below.

| short |     full     | description                                    |
| :---: | :----------: | :--------------------------------------------- |
| `-i`  | `--interval` | Positive integer of iteration time in seconds. |
| `-l`  |   `--log`    | Name of file for logging.                      |
