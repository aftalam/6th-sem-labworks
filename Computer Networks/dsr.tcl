#Program for dynamic source routing algorithm

#10 node example for ad-hoc simulation with DSR
#Define options
set val(chan)       Channel/WirelessChannel     ;   #channel type
set val(prop)       Propagation/TwoRayGround    ;   #radio propagation model
set val(netif)      Phy/WirelessPhy             ;   #network interface type
set val(mac)        Mac/802_11                  ;   #MAC type
set val(ifq)        CMUPriQueue                 ;   #interface queue type
set val(ll)         LL                          ;   #link layer type
set val(ant)        Antenna/OmniAntenna         ;   #antenna model
set val(ifqlen)     50                          ;   #max packet in ifq
set val(nn)         10                          ;   #number of mobilenodes
set val(rp)         DSR                         ;   #routing protocol
set val(x)          500                         ;   #X dimension of topography
set val(y)          400                         ;   #Y dimension of topography  
set val(stop)		50                          ;   #time of simulation end
set ns		        [new Simulator]
set tracefd         [open simple-dsdv.tr w]
set windowVsTime2   [open win.tr w] 
set namtrace        [open aftabdsr.nam w]    
$ns trace-all $tracefd
$ns use-newtrace 
$ns namtrace-all-wireless $namtrace $val(x) $val(y)
#Set up topography object
set topo    [new Topography]
$topo load_flatgrid $val(x) $val(y)
create-god $val(nn)
#Create nn mobilenodes [$val(nn)] and attach them to the channel 
#Configure the nodes
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
for {set i 0} {$i < $val(nn)} {incr i} {
	$node_($i) set X_ [expr rand()*500]
	$node_($i) set Y_ [expr rand()*400]
	$node_($i) set Z_ 0
} 
#Set a TCP connection between node(0) and node(1)
set tcp [new Agent/TCP/Newreno]
$tcp set class_ 2
set sink [new Agent/TCPSink]
$ns attach-agent $node_(0) $tcp
$ns attach-agent $node_(9) $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns at 2.0 "$ftp start" 
for {set i 0} {$i<$val(nn)} {incr i} {
$ns initial_node_pos $node_($i) 30
}
#Telling nodes when the simulation ends
for {set i 0} {$i < $val(nn) } { incr i } {
    $ns at $val(stop) "$node_($i) reset";
}
#Ending nam and the simulation 
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"
$ns at 150.01 "puts \"end simulation\" ; $ns halt"
proc stop {} {
    global ns tracefd namtrace
    $ns flush-trace
    close $tracefd
    close $namtrace
    exec nam aftabdsr.nam &
}
puts "running nam"
$ns run
