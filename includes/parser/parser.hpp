#ifndef PARSER_HPP
#define PARSER_HPP

#include <header.hpp>


class Parser {
    public:
        explicit Parser(const std::string&);
        ~Parser();

        void printVertex() const;
        void printIndices() const;
        [[nodiscard]] const std::vector<float> &getVertex() const;

        [[nodiscard]] const std::vector<u_int> &getIndices() const;

    private:

    std::vector<float> _vertex;
    std::vector<u_int> _indices;
    float _minx;
    float _miny;
    float _maxx;
    float _maxy;
    float _maxz;
    float _minz;
    void centerVertex();
    void faceIndices(std::vector<std::vector<u_int>>);
    void setFaceColor(u_int, std::vector<float>&);
    void setTextureCords(std::vector<float>&);

};


#endif