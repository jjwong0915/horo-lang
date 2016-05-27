  
#include iostream 
using namespace std ; 
  
struct node { 
    int data ; 
    node* next ; 
} ; 
  
  
int f ( int n ) { 
    if ( n <= 2 ) { 
        return 1 ; 
    } else { 
        return f(n-1) + f(n-2) ; 
    } 
} 
  
  
int main ( ) { 
    int t ; 
    cin >> t ; 
    for ( auto i = 0 ; i != t ; i ++ ) { 
        int n ; 
        cin >> n ; 
        cout << f(n) << endl ; 
    } 
    return 0 ; 
} 
  
