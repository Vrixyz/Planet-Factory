#include <QCoreApplication>

#include "height_map.hpp"
#include "bitmap_image.hpp"
#include <iostream>

void gradient(const rgb_store *col_, const std::string filename)
{
  const unsigned int dim = 50;
  bitmap_image image(10*dim,dim);

  for (unsigned int x = 0; x < 10*dim; ++x)
    {
      for (unsigned int y = 0; y < dim; ++y)
        {
            image.set_pixel(x,y,col_[2*x].red,col_[2*x].green,col_[2*x].blue);
        }
    }
  image.save_image(filename);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    gradient(yarg_colormap, "yarg.bmp");

    std::cout << "fin du programme." << std::endl << std::endl;

    return a.exec();
}
