# MiniGit

A lightweight Git-like version control system written in C++17 that replicates core Git internals including commits, branching, and staging.

Built as a college project to understand Object-Oriented Programming and how version control systems work internally.

---

## Features

- Initialize a repository (`init`)
- Stage files (`add`)
- Create commits (`commit`)
- View commit history (`log`)
- Create and list branches (`branch`)
- Content-addressable storage using hashing
- Plain text object database (no external dependencies)

---

## Usage

minigit init              # initialise a new repo in current folder  
minigit add <file>        # stage a file  
minigit commit <message>  # save a snapshot  
minigit log               # show history  
minigit branch            # list branches  
minigit branch <name>     # create branch  

---

## Getting Started

Clone the repository:

git clone https://github.com/ridhimagarg-rg/NanoGit.git  
cd miniGit  

Build:

make  

Run:

./minigit init  

Clean:

make clean  

---

## Project Structure

miniGit/  
├── Makefile  
├── include/  
│   ├── Utils.h  
│   ├── Commit.h  
│   ├── CommitStore.h  
│   ├── StagingArea.h  
│   ├── BranchManager.h  
│   ├── Logger.h  
│   ├── Repository.h  
│   └── CLI.h  
└── src/  
    ├── Utils.cpp  
    ├── Commit.cpp  
    ├── CommitStore.cpp  
    ├── StagingArea.cpp  
    ├── BranchManager.cpp  
    ├── Logger.cpp  
    ├── Repository.cpp  
    ├── CLI.cpp  
    └── main.cpp  

---

## Architecture

The system is built using composition and follows the Single Responsibility Principle.

Utils → file handling, hashing, timestamps  
Commit → represents commit object  
CommitStore → saves and loads commits  
StagingArea → manages staged files  
BranchManager → handles branches and HEAD  
Logger → prints commit history  
Repository → main controller (facade)  
CLI → command parser  

Flow:

main → CLI → Repository → subsystems  

---

## How It Works

1. Files are staged in the INDEX  
2. Files are hashed and stored as blobs  
3. On commit:
   - snapshot is created
   - commit object is generated
   - linked to parent commit  
4. Branch stores latest commit hash  
5. Log walks commit history  

---

## Data Storage

.minigit/  
├── HEAD  
├── INDEX  
├── objects/  
│   ├── <blob_hash>  
│   └── commit_<commit_hash>  
└── refs/  
    └── heads/  
        ├── main  
        └── <branch>  

All data is stored as plain text.

---

## Hashing

Uses FNV-1a 64-bit hashing.

- Same content → same hash  
- Avoids duplicate storage  
- No external libraries required  

---

## OOP Concepts Used

- Encapsulation  
- Single Responsibility Principle  
- Composition over Inheritance  
- Facade Pattern  

---

## Example

minigit init  
minigit add file.txt  
minigit commit "first commit"  
minigit log  

---

## Limitations

Not implemented:

- merge  
- checkout  
- diff  
- remote repos  
- push / pull  

---

## Built With

- C++17  
- std::filesystem  
- No external libraries  

---

## License

MIT License