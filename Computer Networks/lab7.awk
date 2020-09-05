BEGIN {
pktDrop = 0;
byteDrop = 0;
pktRcd = 0;
byteRcd = 0;
}
{
if (($1 == "d") && ($5 == "tcp") || ($5 == "cbr"))
{
    pktDrop += 1;
    byteDrop += $6;
}
if (($1 == "r") && ($5 == "tcp") || ($5 == "cbr"))
{
    pktRcd += 1;
    byteRcd += $6;
}
}
END {
printf("\nNo of PacketDrop = %d \nNo of BytesDrop = %d \nNo of PacketReceived = %d \nNo of BytesReceived = %d \n", pktDrop, byteDrop, pktRcd, byteRcd);
}
