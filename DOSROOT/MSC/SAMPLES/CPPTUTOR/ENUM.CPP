// ENUM.CPP

// This is an example program from Chapter 2 of the C++ Tutorial. This
//     program demonstrates an enumerated data type.

enum color { red, orange, yellow, green, blue, violet };

void main()
{
    color myFavorite, yourFavorite;
    int i;

    myFavorite = blue;
    i = myFavorite;          // Legal; i = 4

//  yourFavorite = 5;        // Error: cannot convert
                             //     from int to color
    myFavorite = (color)4;   // Legal
}

