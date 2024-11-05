# VectorImages_Project

## Summary
This project was an assignment for the Object Oriented Programming course at my university.
The program is capable of creating and editing vector images. Only a few shapes are supported at the moment with the possibility to be saved as SVG file or a custom txt file.

## Usage
The program is a console application without UI that works by typing the available commands.

### Commands:
`open [fileName]` - opens SVG or txt file with shapes

`print` - prints out all shapes to the console with their properties

`create [type, ...]` - creates a shape of type, each shape take different amount of arguments, that will be listed in a section below

`group [topLeftX, topLeftY, botRightX, botRightY]` - groups all elements that are completely inside the region defined by the topLeft and botRight coordinates

`ungroup [id]` - ungroups the group with id

`insert [id, groupId]` - insert the shape with id into the group with groupId

`extract [id, groupId]` - extract the shape with id into the group with groupId

`hide [id]` - hide the shape with id (the transform functions wont affect the hidden shapes)

`show [id]` - show/unhide shape

`translate [horizontal, vertical, id]` - move shape with id (if no id is passed all shapes will be moved)

`scale [horizontal, vertical, id]` - scale shape with id (if no id is passed all shapes will be scaled)

`save` - saves the file (will ask you to enter file name if the canvas wasn't created by opening a file)

`saveas [fileName]` - will save the file with the given filename

`help` - prints out the available commands

`exit` - terminates the program

### Shapes:
- Arc [center, radius, startAngle, arcWidth, fillColor, borderColor]
- Line [start, end, fillColor, borderColor]
- Polygon [point1, point2, ..., pointN, fillColor, borderColor]
- Rectangle [topLeft, width, height, fillColor, borderColor]

### Colors:
Color is a struct of 4 unsigned chars - red, green, blue, alpha. There are presets of colors that work by typing their names:

- red
- green
- blue
- black
- white
- yellow
- orange
- purple
- transparent

## Supported file formats

### SVG
The program can open and save SVG files but not every shape featured in the SVG file format could be read. The program supports only the shapes listed above.

### txt
It is also possible to save the shapes as a txt file where each shape will be put on a new line in the format of the listed shapes in the Shapes section above.

## Footer
These were the requirements for the project and I haven't developed it further after the course. Although there could be implemented a bit more features in the future.
