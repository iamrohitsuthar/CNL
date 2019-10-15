set ns [ new Simulator ]

$ns color 1 Red
$ns color 2 Blue

set nf [ open a.nam w ]
$ns namtrace-all $nf
set nf1 [ open b.tr w ]
$ns trace-all $nf1

proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam a.nam &
	exit 0	
}

set n0 [ $ns node ]
set n1 [ $ns node ]
set n2 [ $ns node ]
set n3 [ $ns node ]
set n4 [ $ns node ]
set n5 [ $ns node ]
set n6 [ $ns node ]
set n7 [ $ns node ]


$ns duplex-link $n0 $n1 2.0Mb 10ms DropTail
$ns duplex-link $n0 $n2 2.0Mb 10ms DropTail
$ns duplex-link $n1 $n5 1.7Mb 10ms DropTail
$ns duplex-link $n2 $n3 1.0Mb 10ms DropTail
$ns duplex-link $n2 $n4 1.0Mb 10ms DropTail
$ns duplex-link $n4 $n6 1.3Mb 10ms DropTail
$ns duplex-link $n3 $n4 2.3Mb 10ms DropTail
$ns duplex-link $n4 $n5 1.3Mb 10ms DropTail
$ns duplex-link $n3 $n7 2.3Mb 10ms DropTail



$ns duplex-link-op $n0 $n1 orient left
$ns duplex-link-op $n0 $n2 orient right-up
$ns duplex-link-op $n1 $n5 orient up
$ns duplex-link-op $n2 $n4 orient left-up
$ns duplex-link-op $n4 $n5 orient left-down
$ns duplex-link-op $n2 $n3 orient up
$ns duplex-link-op $n4 $n6 orient up
$ns duplex-link-op $n3 $n7 orient up
$ns duplex-link-op $n3 $n4 orient left


$ns queue-limit $n2 $n4 4
$ns queue-limit $n2 $n3 4


$ns duplex-link-op $n2 $n4 queuePos 0.5
$ns duplex-link-op $n2 $n3 queuePos 0.5

# Attach TCP agent from n0 to n6
set tcp1 [ new Agent/TCP ]
$tcp1 set class_ 2
$ns attach-agent $n0 $tcp1
set sink1 [ new Agent/TCPSink ]
$ns attach-agent $n6 $sink1
$ns connect $tcp1 $sink1
$tcp1 set fid_ 1

# Attach FTP over TCP
set ftp [ new Application/FTP ]
$ftp attach-agent $tcp1
$ftp set type_ FTP

$ns at 0.4 "$ftp start"
$ns at 2.4 "$ftp stop"
$ns at 2.5 "$ns detach-agent $n0 $tcp1; $ns detach-agent $n6 $sink1"

# Attach UDP agent fro n0 to n4

set udp1 [ new Agent/UDP ]
$ns attach-agent $n0 $udp1
set null1 [ new Agent/Null ]
$ns attach-agent $n7 $null1
$ns connect $udp1 $null1
$udp1 set fid_ 2

# Set up Constant bit ratio for UDP connection
set cbr [ new Application/Traffic/CBR ]
$cbr attach-agent $udp1
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate 1.5Mb
$cbr set random_ true



$ns at 1.5 "$cbr start"
$ns at 3.6 "$cbr stop"
$ns at 4.0 "finish"

$ns run
