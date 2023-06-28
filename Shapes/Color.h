#ifndef SVG_PROJECT_COLOR_H
#define SVG_PROJECT_COLOR_H

#define red 255, 0, 0, 255
#define green 0, 255, 0, 255
#define blue 0, 0, 255, 255
#define black 0, 0, 0, 255
#define white 255, 255, 255, 255
#define yellow 255, 255, 0, 255
#define orange 255, 165, 0, 255
#define purple 128, 0, 128, 255
#define transparent 0, 0, 0, 0

struct Color
        {
            unsigned char redValue;
            unsigned char greenValue;
            unsigned char blueValue;
            unsigned char alpha;

    Color()
            {
                redValue = 0;
                greenValue = 0;
                blueValue = 0;
                alpha = 0;
            }

            Color(unsigned char redValue, unsigned char greenValue, unsigned char blueValue, unsigned char alpha)
            {
                this->redValue = redValue;
                this->greenValue = greenValue;
                this->blueValue = blueValue;
                this->alpha = alpha;
            }

            bool operator==(const Color& other) const
            {
                return redValue == other.redValue && greenValue == other.greenValue && blueValue == other.blueValue && alpha == other.alpha;
            }

            bool operator!=(const Color& other) const
            {
                return !(*this == other);
            }

            friend std::ostream& operator<<(std::ostream &out, const Color&color)
            {
                out << color.toString();
                return out;
            }

            static Color stringToColor(const std::string string)
            {
                if(string == "red")
                    return Color(red);
                else if(string == "green")
                    return Color(green);
                else if(string == "blue")
                    return Color(blue);
                else if(string == "black")
                    return Color(black);
                else if(string == "white")
                    return Color(white);
                else if(string == "yellow")
                    return Color(yellow);
                else if(string == "orange")
                    return Color(orange);
                else if(string == "purple")
                    return Color(purple);
                else if(string == "transparent")
                    return Color(transparent);
                else
                {
                    throw std::invalid_argument("Invalid color!");
                }
            }

            std::string toString() const
            {
                if(*this == Color(red))
                {
                    return "red";
                }
                else if(*this == Color(green))
                {
                    return "green";
                }
                else if(*this == Color(blue))
                {
                    return "blue";
                }
                else if(*this == Color(black))
                {
                    return "black";
                }
                else if(*this == Color(white))
                {
                    return "white";
                }
                else if(*this == Color(yellow))
                {
                    return "yellow";
                }
                else if(*this == Color(orange))
                {
                    return "orange";
                }
                else if(*this == Color(purple))
                {
                    return "purple";
                }
                else if(*this == Color(transparent))
                {
                    return "transparent";
                }
                else
                {
                    return "rgba(" + std::to_string((int)redValue) + "," + std::to_string((int)greenValue) + "," + std::to_string((int)blueValue) + "," + std::to_string((int)alpha) + ")";
                }
            }
        };
#endif //SVG_PROJECT_COLOR_H
