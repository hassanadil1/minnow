#include "../util/socket.hh"
#include "../util/socket.cc"
#include "../util/address.cc"
#include "../util/file_descriptor.cc"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  TCPSocket socket1 {};
  socket1.connect( Address( host, "http" ) );

  socket1.write( string_view( "GET " + path + " HTTP/1.1\r\n" ) );
  socket1.write( string_view( "Host: " + host + "\r\n" ) );
  socket1.write( string_view( "Connection: close\r\n\r\n" ) );

  while ( not socket1.eof() ) 
  {
    string buffer;
    socket1.read( buffer );
    cout << buffer;
  }
  socket1.close();
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << argv[0] << " HOST PATH\n";
      cerr << "\tExample: " << argv[0] << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { argv[1] };
    const string path { argv[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
