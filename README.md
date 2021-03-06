# NoteDB
A simple and centralized note recording system. A simple interface to record the notes, using your favorite text editor. The note database system then automatically stores, classifies and sorts the notes. Notes can be viewed simply through a CLI, querying the database and retrieveing what is requested.

# Architecture
The NoteDB works by using a thin client for writing and reading the different notes. This client communicates with the note daemon, which is responsible for processing the notes and clustering similar ones together.

Parts:
* Noted - The daemon process 
* Notectl - The thin client

## Git branch topology
This repo is built up by the following branches:
* Master - Release branch, stable release versions
* Development - Most recent development version
* Topic - Topic branches are currently developped features / bug resolves

The topic branches, which are abbreviated T<NW,NS,ND,A><Feature>, is where the development
occurs. The different abbreviations stand for:

* ND - Note daemon feature
* NC - Note client feature
* A	 - Global features
