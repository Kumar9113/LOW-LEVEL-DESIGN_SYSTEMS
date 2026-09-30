# File System — LLD

## 1. Overview

This project implements a simplified **File System** using Object-Oriented Design and the **Composite Design Pattern**.

The system represents files and directories in a hierarchical tree structure.

A directory can contain:

* Files
* Other directories

Example:

```text
root/
├── documents/
│   ├── resume.pdf
│   └── notes.txt
├── photos/
│   └── photo.jpg
└── readme.txt
```

---

## 2. Design Pattern Used

### Composite Design Pattern

The **Composite Pattern** is used because both `File` and `Directory` are treated as `fileSystem` objects.

```text
                 fileSystem
                 /         \
                /           \
             File         Directory
                            |
                       vector<fileSystem*>
                         /          \
                      File       Directory
```

### Pattern Mapping

| Composite Component | Implementation |
| ------------------- | -------------- |
| Component           | `fileSystem`   |
| Leaf                | `File`         |
| Composite           | `Directory`    |
| Client              | `FileSystem`   |

---

## 3. Classes

### `fileSystem`

Base abstract class for all file-system objects.

Responsibilities:

* Store the name
* Define common operations
* Provide polymorphism

```cpp
class fileSystem {
protected:
    string name;

public:
    virtual int getSize() = 0;
    virtual void ls(int level = 0) = 0;
};
```

---

### `File`

Represents an individual file.

Properties:

```text
name
size
```

Operations:

```text
getSize()
ls()
```

A file is a **Leaf** because it cannot contain other objects.

---

### `Directory`

Represents a folder.

It contains:

```cpp
vector<fileSystem*> v;
```

Therefore, a directory can contain:

```text
File
Directory
File
Directory
...
```

Operations:

```text
add()
getSize()
ls()
remove()
```

A directory is the **Composite**.

---

### `FileSystem`

Acts as the main entry point to the system.

It maintains:

```cpp
Directory* root;
```

Responsibilities:

* Maintain root directory
* List the file system
* Calculate total size
* Delete items

---

## 4. Main Operations

### Add File

```cpp
root->add(new File("resume.pdf", 100));
```

### Add Directory

```cpp
Directory* docs = new Directory("documents");

docs->add(new File("resume.pdf", 100));

root->add(docs);
```

---

### List

```cpp
fs.ls();
```

Example:

```text
root/
  documents/
    resume.pdf (100 KB)
    notes.txt (50 KB)
  photos/
    photo.jpg (200 KB)
  readme.txt (20 KB)
```

---

### Get Size

```cpp
fs.getSize();
```

Directory size is calculated recursively.

```text
documents
    resume.pdf = 100
    notes.txt  = 50

documents size = 150 KB
```

If:

```text
photos = 200 KB
readme = 20 KB
```

then:

```text
root = 150 + 200 + 20
     = 370 KB
```

---

### Delete

```cpp
fs.remove("notes.txt");
```

The system recursively searches the directory tree and removes the matching item.

---

## 5. Why Composite?

Without Composite, we would need separate logic:

```cpp
if(item is File) {
    ...
}
else if(item is Directory) {
    ...
}
```

With Composite:

```cpp
fileSystem* item;

item->getSize();
item->ls();
```

The client doesn't need to know whether the object is a `File` or a `Directory`.

This provides **uniform treatment of individual objects and groups of objects**.

---

## 6. Memory Management

This implementation intentionally uses simple raw pointers.

```cpp
vector<fileSystem*> v;
```

The `Directory` owns its children.

When a directory is destroyed:

```cpp
~Directory() {
    for(auto child : v) {
        delete child;
    }
}
```

the objects inside it are also deleted.

The base class has a virtual destructor:

```cpp
virtual ~fileSystem() {}
```

This is important because objects are deleted through a base-class pointer.

---

## 7. Time Complexity

Let `N` be the total number of files and directories.

### `ls()`

```text
O(N)
```

Every item is visited once.

### `getSize()`

```text
O(N)
```

Every file/directory is traversed.

### `remove()`

Worst case:

```text
O(N)
```

because we may need to search the entire tree.

### Space Complexity

For recursive traversal:

```text
O(H)
```

where `H` is the maximum directory depth.

The tree itself requires:

```text
O(N)
```

space.

---

## 8. Object Relationship

```text
FileSystem
    |
    | owns
    ↓
 Directory (root)
    |
    | contains
    ↓
 fileSystem*
    |
    +------ File
    |
    +------ File
    |
    +------ Directory
                |
                +------ File
                +------ File
```

This is a **composition relationship** because a directory manages the lifetime of its children.

---

## 9. Interview Explanation

If asked:

### "Why did you use Composite?"

Answer:

> "A file system naturally forms a tree where a directory can contain both files and other directories. I use the Composite Pattern so that both File and Directory implement a common fileSystem interface. This allows operations such as listing and calculating size to be performed uniformly and recursively."

### "What is the Leaf?"

> `File` is the leaf because it cannot contain other file-system objects.

### "What is the Composite?"

> `Directory` is the composite because it can contain multiple `fileSystem` objects.

### "Why is `vector<fileSystem*>` used?"

> "Because a directory can contain both File and Directory objects, so I store pointers to their common base class."

### "Why virtual destructor?"

> "Because derived objects such as File and Directory may be deleted through a `fileSystem*` pointer, so the base destructor must be virtual."

---

## 10. Future Extensions

The current implementation can be extended with:

```text
1. Path-based navigation
2. mkdir()
3. touch()
4. pwd()
5. cd()
6. find()
7. Copy / Move
8. File permissions
9. File metadata
10. Concurrency
11. Observer for file-system events
12. Persistence
```

For the current LLD, **Composite is the primary design pattern**.

---

## 11. Final Design

```text
                  FileSystem
                      |
                     root
                      |
                 Directory
                      |
              vector<fileSystem*>
                 /          \
                /            \
             File          Directory
                              |
                       vector<fileSystem*>
                          /        \
                       File       File
```

### Key Takeaway

```text
Composite Pattern
       ↓
FileSystemItem / fileSystem
       ↓
   ┌───┴────┐
   ↓        ↓
 File    Directory
 Leaf     Composite
```

The core design principle is:

> **Treat individual files and collections of files uniformly through a common interface.**
