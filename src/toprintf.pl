#!/usr/bin/env perl
#
# toprintf.pl
# Encode data to a bunch of bash printf's
# By J. Stuart McMurray
# Created 20250729
# Last Modified 20250908

use autodie;
use strict;
use warnings;

use File::Basename;

# Something like a help statement.
if (0 != 0+@ARGV && "-h" eq $ARGV[0]) {
        print "Usage: @{[basename $0]} [outputfile [localfile]]\n";
        exit 0;
}

# Get the output filename.
my $ofn = shift @ARGV // "/tmp/x";

# Encode each 16-byte chunk to bash printf's.
$" = "";   # Join arrays without spaces.
$/ = \16;  # Work with 16-byte chunks.
$\ = "\n"; # Newline-terminate prints.

print ">$ofn";                                # Truncate the output file.
while (<>) {
        my @bs = unpack "C*";                 # Turn into bytes.
        my @os = map{sprintf "\\%o", $_} @bs; # Turn into octal.
        print "printf '@os' >>$ofn";          # Printfify.
}

