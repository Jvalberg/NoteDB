# NoteDB
A simple and centralized note recording system. A simple interface to record the notes, using your favorite text editor. The note database system then automatically stores, classifies and sorts the notes. Notes can be viewed simply through a CLI, querying the database and retrieveing what is requested.

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
