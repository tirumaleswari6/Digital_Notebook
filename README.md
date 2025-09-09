# 📒 Digital Notebook (C Project)

A simple **Digital Notebook application written in C** that allows users to create, view, search, edit, and delete notes.  
This project is lightweight, beginner-friendly, and useful to showcase **file handling and structured programming in C**.

---

## ✨ Features
- ➕ Add a new note  
- 📖 View all saved notes  
- 🔍 Search notes by keyword  
- ✏️ Edit an existing note  
- ❌ Delete a specific note  
- 🗑️ Delete all notes  

---

## 🛠️ How It Works
- Notes are stored in a binary file named `notes.dat` so they **persist even after closing the program**.  
- Each note contains:
  - **Title** (up to 50 characters)  
  - **Content** (up to 500 characters)  

---

##  How to Compile and Run

### On Windows (using **Visual Studio Developer Command Prompt**):
```bash
cl /EHsc Digital_Notebook.c
Digital_Notebook.exe

or we can run it On Windows (using GCC/MinGW),Linux / MacOS

##File structure
Digital-Notebook/
│── Digital_Notebook.c   # Source code
│── notes.dat            # Created automatically to store notes
│── README.md            # Project documentation


Sample Output
===== Digital Notebook =====
1. Add Note
2. View Notes
3. Search Note
4. Edit Note
5. Delete Note
6. Delete All Notes
7. Exit
Enter choice:
