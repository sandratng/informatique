#include "svgfile.h"
#include <iostream>
#include <sstream>

const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

bool Svgfile::s_verbose = true;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{

    if (s_verbose)
        std::cout << "Opening SVG output file : "
                  << m_filename << std::endl;

    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    if (s_verbose)
        std::cout << "OK" << std::endl;

    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);

    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}

void Svgfile::addDisk(double x, double y, double r, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", color )
            << "/>\n";
}

void Svgfile::addDiskC(double x, double y, double r, std::string fileName,std::string color)
{
    m_ostrm << "<a "
            << attrib("href", fileName)
            << ">"
            << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", color )
            << "/></a>\n";
}

void Svgfile::addsquare(double x, double y, double l, double l2,std::string colorFill)
{

    m_ostrm << "<polygon points=\" ";

        m_ostrm
            << x << "," << y << " "
            << x+l << "," << y << " "
            << x+l << "," << y+l2 << " "
            << x << "," << y+l2
          << "\" style=\"fill:" << colorFill
            << "\" />\n";
}
void Svgfile::addCircle(double x, double y, double r, double ep, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", "none")
            << attrib("stroke", color )
            << attrib("stroke-width", ep )
            << "/>\n";
}

/// <polygon points="200,10 250,190 160,210" style="fill:lime;stroke:purple;stroke-width:1" />
void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke)
{

    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}


void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}

void Svgfile::addPolygon(double x1, double y1, double x2, double y2,
                          double x3, double y3,double x4, double y4, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3 << " "
            << x4 << "," << y4
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}

void Svgfile::addLine(double x1, double y1, double x2, double y2, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color)
            << "/>\n";
}

void Svgfile::addCross(double x, double y, double span, std::string color)
{
    addLine(x-span, y-span, x+span, y+span, color);
    addLine(x-span, y+span, x+span, y-span, color);
}

void Svgfile::addText(double x, double y, std::string text, std::string color)
{
    /// <text x="180" y="60">Un texte</text>
    m_ostrm << "<text "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("fill", color)
            << ">" << text << "</text>\n";
}

void Svgfile::addText(double x, double y, double val, std::string color)
{
    std::ostringstream oss;
    oss << val;
    addText(x, y, oss.str(), color);
}
void Svgfile::addRectangle(double x, double y,double width ,double height, std::string colorFill)
{
    m_ostrm << "<rect x=\" "
            << x << "\"  y=\" "
            << y << "\"  width=\" "
            << width << "\" height=\" "
            << height << "\" style=\" fill:"
            << colorFill
            << "\" />\n";
}

void Svgfile::addGrid(double span, bool numbering, std::string color)
{
    double y=0;
    addRectangle(0,0,2,m_height,"black");
    addRectangle(0,798,m_width,2,"black");
    addLine(0,0,10,10,"black");
    addLine(1000,800,990,790,"black");
    addText(20,30,"COUT 2","black");
    addText(930,770,"COUT 1", "black");
    while (y<=m_height)
    {
        addLine(0, y*10, m_width*10, y*10, color);
        if (numbering)
            addText(5, m_height-y*10-5, y, color);
        y+=span;
    }

    double x=0;
    std::cout<< m_width;
    while (x<=m_width)
    {
        addLine(x*10, 0, x*10, m_height*10  , color);
        if (numbering)
            addText(x*10+5, m_height-5, x, color);
        x+=span;
    }
}

void Svgfile::addGrid(double span, double span2, bool numbering, std::string color)
{
    double y=0;
    addRectangle(0,0,2,m_height,"black");
    addRectangle(0,798,m_width,2,"black");
    addLine(0,0,10,10,"black");
    addLine(1000,800,990,790,"black");
    addText(20,30,"COUT 2","black");
    addText(930,770,"COUT 1", "black");
    while (y<=m_height)
    {
        addLine(0, y*5, m_width*5, y*5, color);
        if (numbering)
            addText(5, m_height-y*5-5, y*span2, color);
        y+=span;
    }

    double x=0;
    std::cout<< m_width;
    while (x<=m_width)
    {
        addLine(x*5, 0, x*5, m_height*5  , color);
        if (numbering)
            addText(x*5+5, m_height-5, x, color);
        x+=span;
    }
}

std::string Svgfile::makeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}
