# Week 4 CS50X

All files are from week 4 of Harvard CS50X - Memory

- **Filter** - A program that applies filters to BMPs 📷
  - Implement the functions in helpers.c such that a user can apply grayscale, sepia, reflection, or blur filters to their images
    - The function grayscale should take an image and turn it into a black-and-white version of the same image.
    - The function sepia should take an image and turn it into a sepia version of the same image.
    - The reflect function should take an image and reflect it horizontally.
    - The blur function should take an image and turn it into a box-blurred version of the same image.

- **Recover** - A program called recover that recovers JPEGs from a forensic image. 🔍
  - Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.
  - If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return 1.
  - If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
  - Your program, if it uses malloc, must not leak any memory.