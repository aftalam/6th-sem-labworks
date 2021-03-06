#Program for wireless network simulation

#Wireless Network Simulation - as the nodes come within their hearing range, the packets are exchanged 

#define options

set val(chan)       Channel/WirelessChannel	;       #channel type
set val(prop)       Propagation/TwoRayGround ;      #radio propagation model
set val(netif)      Phy/WirelessPhy ;               #network interface type
set val(mac)        Mac/802_11 ;                    #MAC type
set val(ifq)        Queue/DropTail/PriQueue ;       #interface queue type
set val(ll)         LL ;                            #link layer type
set val(ant)        Antenna/OmniAntenna ;           #antenna model
set val(ifqlen)     50 ;                            #max packet in ifq
set val(nn)         3 ;                             #number of mobilenodes
set val(rp)         DSDV ;                          #routing protocol
set val(x)          500 ;                           #X dimension of topography
set val(y)          400 ;                           #Y dimension of topography  
set val(stop)       150 ;                           #time of simulation end

set ns              [new Simulator]
set tracefd         [open xwrls-simple.tr w]
set windowVsTime2   [open xwrls-simple-win.tr w] 
set namtrace        [open aftab7.nam w]    
$ns trace-all $tracefd
$ns namtrace-all-wireless $namtrace $val(x) $val(y)

#setup topography object

set topo    [new Topography]
$topo load_flatgrid $val(x) $val(y)
create-god $val(nn)

#configure the nodes

$ns node-config -adhocRouting $val(rp) \
-llType $val(ll) \
-macType $val(mac) \
-ifqType $val(ifq) \
-ifqLen $val(ifqlen) \
-antType $val(ant) \
-propType $val(prop) \
-phyType $val(netif) \
-channelType $val(chan) \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON \
-macTrace OFF \
-movementTrace ON

for {set i 0} {$i < $val(nn) } { incr i } {
set node_($i) [$ns node]	
}

#provide initial location of mobilenodes

$node_(0) set X_ 5.0
$node_(0) set Y_ 5.0
$node_(0) set Z_ 0.0
$node_(1) set X_ 490.0
$node_(1) set Y_ 285.0
$node_(1) set Z_ 0.0
$node_(2) set X_ 150.0
$node_(2) set Y_ 240.0
$node_(2) set Z_ 0.0

#generation of movements

$ns at 10.0 "$node_(0) setdest 250.0 250.0 3.0"
$ns at 15.0 "$node_(1) setdest 45.0 285.0 5.0"
$ns at 110.0 "$node_(0) setdest 480.0 300.0 5.0" 

#setup a TCP connection between node_(0) and node_(1)

set tcp [new Agent/TCP/Newreno]
$tcp set class_ 2
set sink [new Agent/TCPSink]
$ns attach-agent $node_(0) $tcp
$ns attach-agent $node_(1) $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns at 10.0 "$ftp start" 

#printing the window size

proc plotWindow {tcpSource file} {
global ns	
set time 0.01
set now [$ns now]
set cwnd [$tcpSource set cwnd_]
puts $file "$now $cwnd"
$ns at [expr $now+$time] "plotWindow $tcpSource $file" }
$ns at 10.1 "plotWindow $tcp $windowVsTime2"  

#define node initial position in nam

for {set i 0} {$i < $val(nn)} { incr i } {
#30 defines the node size for nam
$ns initial_node_pos $node_($i) 30
}

#telling nodes when the simulation ends

for {set i 0} {$i < $val(nn) } { incr i } {
$ns at $val(stop) "$node_($i) reset";
}

#ending nam and the simulation

$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"
$ns at 150.01 "puts \"end simulation\" ; $ns halt"
proc stop {} {
global ns tracefd namtrace
$ns flush-trace
close $tracefd
close $namtrace
exec nam aftab7.nam &
}
puts "running nam"
$ns run
