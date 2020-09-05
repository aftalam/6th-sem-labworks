#Program for ethernet lan using n nodes

#Create a simulator object
set ns [new Simulator]
#Define color for data flow (for nam)
$ns color 0 blue
#Open the nam trace file
set nf [open aftab.nam w]
$ns namtrace-all $nf
#Open a new file to log trace
set tf [open aftab.tr w]
$ns trace-all $tf
#Define a 'finish' procedure
proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $nf
	close $tf
    exec nam aftab.nam &
    exec awk -f aftlan.awk aftab.tr &
    exit 0
}
#Create ten nodes with color
set n0 [$ns node]
$n0 color red
set n1 [$ns node]
$n1 color red
set n2 [$ns node]
$n2 color red
set n3 [$ns node]
$n3 color red
set n4 [$ns node]
$n4 color red
set n5 [$ns node]
$n5 color red
set n6 [$ns node]
$n6 color red
set n7 [$ns node]
$n7 color red
set n8 [$ns node]
$n8 color red
set n9 [$ns node]
$n9 color red
set n10 [$ns node]
$n10 color red
#Create a local area network (LAN) of 10 nodes
$ns make-lan "$n0 $n1 $n2 $n3 $n4 $n5 $n6 $n7 $n8 $n9 $n10" 100Mb 20ms LL Queue/DropTail Mac/802_3
#Create TCP agent between node 0 and node 3
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set sink0 [new Agent/TCPSink]
$ns attach-agent $n3 $sink0
$ns connect $tcp0 $sink0
#Create FTP application for TCP agent
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
#Specify TCP packet size
Agent/TCP set packetSize_ 1000
#Start and Stop FTP Traffic
$ns at 0.75 "$ftp0 start"
$ns at 4.75 "$ftp0 stop"
#Stop the simulation
$ns at 5.0 "finish"
puts "running nam"
#Run the simulation
$ns run
