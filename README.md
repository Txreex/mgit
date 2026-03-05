# mgit — A Minimal Git Implementation in C++

`mgit` is a simplified implementation of Git written in C++ to understand how version control systems work internally.

Instead of treating Git as a black box, this project rebuilds the core object model that powers Git: blobs, trees, commits, and the staging area.

The goal of this project is to explore how Git stores repositories as **content-addressable objects rather than file diffs.**

---

## Features

- Blob objects for file contents
- Tree objects representing directory structure
- Commit objects linking snapshots
- SHA-1 content-addressable object storage
- Staging area (index)
- Recursive directory tracking
- Parent commit history
- Minimal CLI interface

---

## Project Structure

```
mgit/
│
├── commands/
│   ├── init.cpp
│   ├── add.cpp
│   └── commit.cpp
│
├── objects/
│   ├── blob.cpp
│   ├── tree.cpp
│   └── object_store.cpp
│
├── index/
│   └── index.cpp
│
├── hashing/
│   └── sha1.cpp
│
├── repo/
│   └── repo.cpp
│
└── main.cpp
```

---

## How It Works

Git stores data as immutable objects identified by their SHA-1 hash.

The basic object chain looks like this:

```
file → blob → tree → commit
```

### Blob

Stores file contents.

```
blob <size>\0<file content>
```

### Tree

Represents directories and links files or subdirectories.

### Commit

Stores metadata and links a snapshot of the repository.

```
commit
 ├─ tree
 ├─ parent
 └─ message
```

Each commit points to a tree representing the repository at that moment.

---

## Usage

### Initialize repository

```
./mgit init
```

Creates:

```
.mgit/
├── objects/
├── index
└── HEAD
```

---

### Add files

```
./mgit add file.txt
./mgit add folder/
./mgit add .
```

Files are hashed and stored as blob objects.

---

### Commit changes

```
./mgit commit "initial commit"
```

This command:

1. Builds a tree from the staged files
2. Creates a commit object
3. Updates the HEAD pointer

---

## Example Workflow

```
./mgit init

echo "hello world" > hello.txt

./mgit add hello.txt
./mgit commit "first commit"
```

Objects created:

```
.mgit/objects/
├── blobs
├── trees
└── commits
```

---

## Build

Compile the project with:

```
clang++ -std=c++17 \
main.cpp \
commands/init.cpp \
commands/add.cpp \
commands/commit.cpp \
objects/blob.cpp \
objects/tree.cpp \
objects/object_store.cpp \
hashing/sha1.cpp \
index/index.cpp \
repo/repo.cpp \
-o mgit
```

---

## Motivation

Git is one of the most widely used tools in software development, yet its internal architecture is rarely explored.

This project was built to better understand:

- content-addressable storage
- snapshot-based version control
- how commits form a history graph
- how Git manages repository state

---

## Future Improvements

- `mgit log`
- `mgit checkout`
- branch support
- merge functionality
- object compression

---

## References

- Pro Git Book
- Write Yourself a Git (WYAG)
- Git source code

---

## Author

Tanay Singh