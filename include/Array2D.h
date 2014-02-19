/// Class for easily passing 2D arrays, I had done this without the use of a
/// wrapper or pointers in the original Maze Game, but I can't remember how.
#ifndef ARRAY2D
#define ARRAY2D
template<class T>
class Array2D
{
    protected:
        T* data;
    public:
        const unsigned int rows, cols, size;

        // Constructor
        Array2D(unsigned int r, unsigned int c)
            : rows(r), cols(c), size(r*c)
        {
            data = new T[size];
        }

        // Destructor
        ~Array2D()
        {
            delete data;
        }

        // Accessor
        void
};
#endif // ARRAY2D
