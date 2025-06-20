/*
input = "200.23.16.0/28";
ip, mask = input.split("/");
uint32_t address, netmask;

// split ip into four octets based on '.'
for(int i = 0; i < 4; i++)
{
    address = address << 8;
    address += octet;
}

Example: 
"200.20.16.0"
vector octets = {"200", "20", "16", "0"};
(for int i = 0; i <4; i++) {
    // i = 0
    address = address << 8;                     // address = 0x00000000 (this is hex, not binary!)
    address += stoi(octets[i]);                 // address = 0x000000c8

    // i = 1
    addres = address << 8;                      // address = 0x0000c800
    address += stoi(octete[i]);                 // address = 0x0000c814

    // i = 2
    addres = address << 8;                      // address = 0x00c81400
    address += stoi(octete[i]);                 // address = 0x00c81410

    // i = 3
    addres = address << 8;                      // address = 0xc8140000
    address += stoi(octete[i]);                 // address = 0xc8141000
}
    // 11001000 00010111 00010000 00000000  - binary equivalent of the above hex address

mask_length = 28;
uint32_t mask = 0;
for(int i = 0; i < mask_length; i++)
{
    mask << 1;
    mask += 1;
}

mask = mask << (32 - mask_length);

// 0xfffffff0 - 11111111 11111111 11111111 11110000

address = 11001000 00010111 00010000 00000000;
mask = 11111111 11111111 11111111 11110000;

net_addr = address & mask;
bcast = net_addr |~ mask;                          // take complement of mask (switch all 0's to 1's and vis versa), and or with net_adrr

usable_addr = 2^(32 - mask_length) - 2;            // could do: loop (not optimal but doable), pow()
// usable_addr = bcast - net_addr - 1;

for(int i net_addr + 1; i < bcast; i++) { print }; 
*/

// 159.242.0.0/16 --> usable addresses = 2^16 - 2 
// 159.242.0.0/21 --> usable addresses = 2^11 - 2   // subtract /21 from 32
    // net address = 159.242.0.0
    // bcast address = 159.242.7.255