# OpenGL Paint

A MS Paint-style 2D drawing application built with C++ and OpenGL featuring essential drawing tools, shape primitives, and advanced features like undo/redo functionality.

## Features

### Drawing Tools
- **Shape Primitives**: Draw lines, rectangles, and circles with precision
- **Freehand Drawing**: Natural drawing experience with smooth pen tool
- **Fill Tool**: Intelligently fill enclosed areas with selected colors
- **Color Palette**: Easy color selection for all drawing operations

### Advanced Features
- **Undo/Redo Functionality**: Full support for reverting and reapplying actions
- **Command Pattern**: Clean, extensible architecture for tool operations
- **Double-Buffered Rendering**: Smooth, flicker-free drawing experience
- **Interactive UI**: Intuitive controls for mode switching and color selection

## Screenshots

| Screenshot 1 | Screenshot 2 | Screenshot 3 |
|---|---|---|
| [<img width="982" height="932" alt="1" src="https://github.com/user-attachments/assets/91702ce6-3f0f-4c00-8df3-5ca5b14e5860" />]
 | [<img width="1094" height="819" alt="2" src="https://github.com/user-attachments/assets/0873cf82-6c9c-49d8-a72e-1f3223a3e282" />]
| [<img width="1350" height="807" alt="3" src="https://github.com/user-attachments/assets/19753e1d-ec9b-42e6-9d38-6a5bc8b4f426" />]
 |

## Technology Stack

- **Language**: C++ (48.5%)
- **Graphics**: OpenGL
- **Build System**: Makefile
- **Additional**: Python (25.7%), C (25%)

## Architecture Highlights

### Design Patterns
- **Command Pattern**: Each drawing action is encapsulated as a command object, enabling undo/redo functionality
- **Double Buffering**: Uses two rendering buffers to eliminate flickering and provide smooth animations

### Rendering Pipeline
- OpenGL-based 2D rendering with optimized graphics primitives
- Efficient shape rendering for lines, rectangles, and circles
- Real-time color application and fill operations

## Getting Started

### Prerequisites
- C++ compiler (C++11 or later)
- OpenGL 3.0 or higher
- GLFW or similar windowing library
- GLM for mathematics operations

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/rathod-dhruv/OpenGL-Paint.git
cd OpenGL-Paint

# Compile using Makefile
make

# Run the application
./paint
```

### Usage

1. **Select a Tool**: Choose from the toolbar (pen, line, rectangle, circle, fill)
2. **Pick a Color**: Click on the color palette to select your drawing color
3. **Draw**: Click and drag on the canvas to create shapes or freehand drawings
4. **Undo/Redo**: Use Ctrl+Z to undo and Ctrl+Y to redo actions
5. **Fill**: Select the fill tool and click within a closed area to fill it

## Project Structure

```
OpenGL-Paint/
├── src/                 # Source code
│   ├── main.cpp        # Entry point
│   ├── drawing/        # Drawing tools implementation
│   ├── shapes/         # Shape primitives
│   ├── commands/       # Command pattern implementation
│   └── rendering/      # OpenGL rendering logic
├── Makefile            # Build configuration
├── README.md           # This file
└── docs/               # Additional documentation
```

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues to suggest improvements or report bugs.

## Future Enhancements

- [ ] Layer support for non-destructive editing
- [ ] Text tool with font selection
- [ ] Advanced brush styles and textures
- [ ] Image import/export functionality
- [ ] Selection and transformation tools
- [ ] Cross-platform GUI framework integration

## License

This project is open source. See LICENSE file for details.

## Author

**Dhruv Rathod**

---

**Project Details**
- Repository: [rathod-dhruv/OpenGL-Paint](https://github.com/rathod-dhruv/OpenGL-Paint)
- Language Composition: C (48.5%), Python (25.7%), C++ (25%)
- Type: Graphics Application / Drawing Tool
