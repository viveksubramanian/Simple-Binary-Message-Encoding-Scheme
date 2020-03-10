/*This encodes a binary payload using Run Length Encoding (RLE). Since it is specified
 * that the message is binary, RLE is considered, which is particularly helpful when there are a number
 * of repetitions  of 0's or 1's. In the case of characters, probability based on the number of
 * occurrences would have been assigned and a (Prefix)/Huffman code would have been considered.
 * Input - messagePayload.txt path
 * Output - Original binary message is decoded (can be written to a file if required).
 */
#include "main.h"
#include <fstream>

char* binary_payload_path; // Path to the directory containing the bytes.


//  Message header map
std::map<string, string> Message::function()
{
    std::map<string, string> header;
    return header;
}

/*Method to read a binary payload from a text file. For the sake of convenience
* it is assumed that the message is contained in a text file.*/
vector<int> Message::returnArray(char *binary_payload_path)
{
    int read_number;
    vector<int> arr;

    cout<<binary_payload_path << "\n";
    std::ifstream in(binary_payload_path);

    while (in >> read_number)
    {
        arr.push_back(read_number);
    }
    return arr;
}


vector<int> Codec::encode(unsigned long size, vector<int> &byte_stream)
{
    int count =1;
    vector<int> rle;
    cout<<"\n";
    for (int i = 0; i < size; i++)
    {
        cout<<byte_stream[i];
    }
    std::cout<<std::endl;
    rle.push_back(byte_stream[0]);    //The first element of the vector is the first digit of the bit stream
    for (int  j = 0;  j<size ; j++)
    {
        if(byte_stream[j] == byte_stream[j+1])
        {
            count +=1;
        }
        else {
            rle.push_back(count);   // the count values are added to the vector
            count = 1;
        }
    }
    return rle;
}


/* Assign a 0 or 1 to every value alternately since each digit denotes a change in values 'n' times.
 * It does not matter what it is initially. Now use the first byte that you stored in encoded_stream[0] to know
 * the starting value and change it accordingly.
 * */
vector<int> Codec::decode(unsigned long size, vector<int>& encoded_stream)
{
    vector<int> original;
    int first_digit = encoded_stream[0];
    for (int i = 1; i < size; i++)
    {
        int n = encoded_stream[i];

        if (first_digit ==0)
        {
            if(i%2==0)
            {
                for (int j=0; j<n; j++)
                {
                    original.push_back(1);
                }
            }
            else {
                for (int j=0; j<n; j++)
                {
                    original.push_back(0);
                }
            }
        }

        else {
            if(i%2==0)
            {
                for (int j=0; j<n; j++)
                {
                    original.push_back(0);
                }
            }
            else {
                for (int j=0; j<n; j++)
                {
                    original.push_back(1);
                }
            }
        }
    }
    cout<<"\n";

    return original;
}

int main(int argc, char **argv)
{

    Message m;
    Codec c;

    binary_payload_path = (char*) malloc(strlen(argv[1]));
    strcpy(binary_payload_path, argv[1]);

//    Read the binary stream from the text file and store it in a vector
    vector<int> byte_stream = m.returnArray(binary_payload_path);
    unsigned long byte_stream_size = byte_stream.size();
    for (int i = 0; i < byte_stream.size(); i++)
    {
        cout<<byte_stream[i];
    }

//    Input the binary stream stored in the vector into the encoder and the encoded
//    stream is stored in another vector
    vector<int> encoded_stream = c.encode(byte_stream_size,byte_stream);
    unsigned long encoded_stream_size = encoded_stream.size();
    for (int j = 0; j < encoded_stream.size(); j++)
    {
        cout<<encoded_stream[j];
    }

//    Input the encoded stream into the decoder to get the decoded original message
    vector<int> decoded_stream = c.decode(encoded_stream_size,encoded_stream);
    for (int j = 0; j < decoded_stream.size(); j++)
    {
        cout<<decoded_stream[j];
    }

    free(binary_payload_path);
    return 0;
}



