# program to remove a leading UTF-8 BOM from a file
# works both STDIN -> STDOUT and on the spot (with filename as argument)

if ($#ARGV > 0) {
    print STDERR "Too many arguments!\n";
    exit;
    }

my @file;   # file content
my $lineno = 0;

my $filename = @ARGV[0];
if ($filename) {
    open( BOMFILE, $filename ) || die "Could not open source file for reading.";
    while (<BOMFILE>) {
        if ($lineno++ == 0) {
            if ( index( $_, '?' ) == 0 ) {
                s/^\xEF\xBB\xBF//;
                print "BOM found and removed.\n";
                }
            else { print "No BOM found.\n"; }
            }
        push @file, $_ ;
        }
    close (BOMFILE)  || die "Can't close source file after reading.";

    open (NOBOMFILE, ">$filename") || die "Could not open source file for writing.";
    foreach $line (@file) {
        print NOBOMFILE $line;
        }
    close (NOBOMFILE)  || die "Can't close source file after writing.";
    }
else {  # STDIN -> STDOUT
    while (<>) {
    if (!$lineno++) {
        s/^\xEF\xBB\xBF//;
        }
    push @file, $_ ;
    }

    foreach $line (@file) {
        print $line;
        }
    }
