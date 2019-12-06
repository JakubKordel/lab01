#include <iostream>
#include <vector>
#include <string>

std::vector<int> findKMP(std::string const & str, std::string const & text){
    int tab[str.length()+1];
    int b = -1;
    tab[0] = -1;
    for ( unsigned int i = 1; i <= str.length() ; ++i ){
        while ( b > -1 && str[b] != str[i - 1] )
            b = tab[b];
        ++b;
        if (i == str.length() || str[i] != str[b] )
            tab[i] = b;
        else
            tab[i] = tab[b];
    }



    std::vector<int> pos;
    int position = -1;
    b = 0;
    for (int i = 0; i < text.length(); ++i  ){
        while ( b > -1 && str[b] != text[i])
            b = tab[b];
        b = b + 1;
        if ( b < str.length() )
            continue ;
        position = i - b + 1;
        pos.push_back( position );
        b = tab[b];
    }
    if ( position == -1 )
        pos.push_back( -1 );
    return pos;
}

int main()
{
    std::vector<int> result = findKMP("abc", "fahghdfghaabchdfsjka");
    for (int i = 0; i < result.size() ; ++i )
        std::cout << result[i] << "  ";
    return 0;
}
