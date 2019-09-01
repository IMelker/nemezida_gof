// Приспособленец (Flyweight)

#include <iostream>
#include <map>

struct Image
{
    void resize(int, int) {};
};

class ImageResizer
{
    std::map<int, Image> images;
  public:
    Image getBox(int width) {
        auto it = images.find(width);

        if (it == images.end()) {
            std::cout << "Create new image with side width: " << width << std::endl;

            Image img;
            img.resize(width, width);

            std::tie(it, std::ignore) = images.emplace(width, img);
        } else {
            std::cout << "Get image from map with side width: " << width << std::endl;
        }

        return it->second;
    }
};

int main(int, char *[]) {
    ImageResizer rs;

    rs.getBox(128);
    rs.getBox(1024);
    rs.getBox(2565);

    rs.getBox(128);
    rs.getBox(1024);
    rs.getBox(4096);
}
