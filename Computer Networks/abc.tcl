set ns [new Simulater]
$ns color 1 Blue
$ns 2 Red

set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
global ns nf
$ns flush-trace
close $nf
exec nam-a out.nam&
exit0
}
set n0[$ns node]
set n1[$ns node]
set n2[$ns node]
set n3[$ns node]
set sbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_500
$cbr1 set interval_0.005
$cbr1 attach-agent$udp1

set null0[new Agent/Null]
$ns attach-agent $n3 $null0

$ns connect $udp0 $null()
$ns connect $udp1 $null()

$ns at 0.5 "$scbr0 start"
$ns at 1.0 "$scbr1 start"
$ns at 4.0 "$scbr1 stop"
$ns at 4.5 "$scbr0 stop"
$ns at 5.0 "finish"
$ns run
