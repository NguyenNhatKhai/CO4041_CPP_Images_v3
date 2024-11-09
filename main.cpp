//

#include "main.h"

using namespace std;

// #define CHANNEL_SIMULATOR decoder_0.channel_path = channel_0.skip();
// #define CHANNEL_SIMULATOR decoder_0.channel_path = channel_0.random_1s1p(0.001);
// #define CHANNEL_SIMULATOR decoder_0.channel_path = channel_0.gilbert_elliot_2s2p(0.00025, 0.25);
#define CHANNEL_SIMULATOR decoder_0.channel_path = channel_0.gilbert_elliot_2s4p(0.00035, 0.25, 0.00001, 0.75);

int main(int argc, char* argv[]) {
    cout << get_current_time() << "\tPreparing" << endl;
    Source source_0("Source/source_0");
    Encoder encoder_0("", "Encoder/encoder_0");
    Channel channel_0("", "Channel/channel_0");
    Decoder decoder_0("", "Decoder/decoder_0", encoder_0.encoder_path);
    Sink sink_0("", "Sink/sink_0");
    ofstream bit_error_rate_file((string)argv[1] + ".txt");
    bit_error_rate_file.close();

    cout << get_current_time() << "\tLoading data to source" << endl;
    encoder_0.source_path = source_0.get_image("Image/image_0");

    cout << get_current_time() << "\tSimulating 1st scenario" << endl;
    channel_0.encoder_path = encoder_0.skip();
    CHANNEL_SIMULATOR
    sink_0.decoder_path = decoder_0.skip();
    sink_0.get_image();
    // sink_0.set_image("Image/image_1");
    write_bit_error_rate((string)argv[1], source_0.source_path, sink_0.sink_path);

    cout << get_current_time() << "\tSimulating 2nd scenario" << endl;
    channel_0.encoder_path = encoder_0.reed_solomon();
    CHANNEL_SIMULATOR
    sink_0.decoder_path = decoder_0.reed_solomon();
    sink_0.get_image();
    // sink_0.set_image("Image/image_2");
    write_bit_error_rate((string)argv[1], source_0.source_path, sink_0.sink_path);

    cout << get_current_time() << "\tSimulating 3rd scenario" << endl;
    channel_0.encoder_path = encoder_0.reed_solomon_hamming();
    CHANNEL_SIMULATOR
    sink_0.decoder_path = decoder_0.reed_solomon_hamming();
    sink_0.get_image();
    // sink_0.set_image("Image/image_3");
    write_bit_error_rate((string)argv[1], source_0.source_path, sink_0.sink_path);

    cout << get_current_time() << "\tSimulating 4th scenario" << endl;
    channel_0.encoder_path = encoder_0.reed_solomon_hamming_interleave(2);
    CHANNEL_SIMULATOR
    sink_0.decoder_path = decoder_0.reed_solomon_hamming_interleave(2);
    sink_0.get_image();
    // sink_0.set_image("Image/image_4");
    write_bit_error_rate((string)argv[1], source_0.source_path, sink_0.sink_path);

    cout << get_current_time() << "\tSimulating 5th scenario" << endl;
    channel_0.encoder_path = encoder_0.reed_solomon_hamming_interleave(4);
    CHANNEL_SIMULATOR
    sink_0.decoder_path = decoder_0.reed_solomon_hamming_interleave(4);
    sink_0.get_image();
    // sink_0.set_image("Image/image_5");
    write_bit_error_rate((string)argv[1], source_0.source_path, sink_0.sink_path);
    
    cout << get_current_time() << "\tFinishing" << endl;
    return 0;
}

