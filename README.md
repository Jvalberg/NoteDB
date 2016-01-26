# NoteDB
A simple and centralized note recording system. A simple interface to record the notes, using your favorite text editor. The note database system then automatically stores, classifies and sorts the notes. Notes can be viewed simply through a CLI, querying the database and retrieveing what is requested.

# Architecture
The NoteDB works by using thin clients for writing and reading the different notes. These clients communicate with the note daemon, which is responsible for processing the notes and clustering similar ones together.

Parts:
* NoteScribbler		- The Note Writer client
* NoteSeer			- The Note Reader client, a CLI for querying notes
* NoteMastermind	- The Note Daemon, which processes all notes.

## Git branch topology
This repo is built up by the following branches:
* Master - Release branch, stable release versions
* Development - Most recent development version
* Topic - Topic branches are currently developped features / bug resolves

The topic branches, which are abbreviated T<NW,NS,ND,A><Feature>, is where the development
occurs. The different abbreviations stand for:

* NW - The note writer client
* NS - The note reader client
* ND - The note daemon process
* A	 - Global features
