QsLog version 2.0

Changes:
* the file destination supports log rotation
* behaviour change: log files are encoded as UTF-16
* behaviour change: the log appends rather than truncating on every startup when rotation is enabled

Fixes:
* renamed the main.cpp example to avoid QtCreator confusion
* offer a way to check if the destination creation has failed (for e.g files)