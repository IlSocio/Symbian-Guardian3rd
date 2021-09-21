#!perl -w
use strict;

if(@ARGV != 1) {
    print "Usage: fixrtf filename\n";
    exit;
}

open(FIN, $ARGV[0]) or die "Can\'t find $1: $!";

my @lines = <FIN>;
close FIN;
open(FOUT, ">$ARGV[0]");

foreach my $line (@lines) {
    $line =~ s/\{[^\}]*\\wgrffmtfilter.*\}//;
    print FOUT $line;
    }
close FOUT;

