#!/usr/bin/perl
use 5.10.0;
use warnings FATAL => 'all';

use File::Temp;
use File::Copy;
use IO::Handle;

sub scm_eval {
    my ($cmdline) = @_;
    my $tmpcmd = File::Temp->new;
    $tmpcmd->say($cmdline);
    my $tmpcode = File::Temp->new;
    copy("ps3a.rkt", $tmpcode) or die "Copy failed: $!";
    open(my $fh, '>>', $tmpcode);
    $fh->say('(define-namespace-anchor bottlenose-nsa)
(define bottlenose-ns (namespace-anchor->namespace bottlenose-nsa))
(eval (call-with-input-string (vector-ref (current-command-line-arguments) 0) read) bottlenose-ns)');
    my $result = `racket $tmpcode '(load "$tmpcmd")'`;
    chomp $result;
#    print "answer was ", $result, " ";
    return $result;
}

sub scm_equal {
    my ($e0, $e1) = @_;
    my $tmp = File::Temp->new;
    $tmp->say("(equal? $e0 $e1)");
    my $result = `racket -e '(load "$tmp")'`;
    chomp $result;
    return $result eq "#t";
}
sub scm_equal_sign {
    my ($e0, $e1) = @_;
    my $tmp = File::Temp->new;
    $tmp->say("(equal?/recur (list->vector $e0) (list->vector $e1) =)");
    my $result = `racket -e '(load "$tmp")'`;
    chomp $result;
    return $result eq "#t";
}

use Test::Simple tests => 20;

ok(scm_equal(scm_eval("p1_a"), '#t'), "p1_a");
ok(scm_equal(scm_eval("(p1_b1 a)"), 4), "(p1_b1 a)");
ok(scm_equal(scm_eval("(p1_b2 b)"), 4), "(p1_b2 b)");
ok(scm_equal(scm_eval("(p1_b3 c)"), 4), "(p1_b3 c)");
ok(scm_equal(scm_eval("p3"), '#t'), "p3");
ok(scm_equal(scm_eval("p4"), '#t'), "p4");
ok(scm_equal(scm_eval("(list-prod-iter '(1 2 3 4))"), 24), "(list-prod-iter '(1 2 3 4))");
ok(scm_equal(scm_eval("(list-prod-iter '(4 3 2 1))"), 24), "(list-prod-iter '(4 3 2 1))");
ok(scm_equal(scm_eval("(double-list1 '(1 2 3))"), "'(2 4 6)"), "(double-list1 '(1 2 3))");
ok(scm_equal(scm_eval("(double-list2 '(1 2 3))"), "'(2 4 6)"), "(double-list2 '(1 2 3))");
ok(scm_equal(scm_eval("(double-list3 '(1 2 3))"), "'(2 4 6)"), "(double-list2 '(1 2 3))");
ok(scm_equal(scm_eval("(square-list '(1 2 3))"), "'(1 4 9)"), "(square-list '(1 2 3))");
ok(scm_equal(scm_eval("(square-list-using-map '(1 2 3))"), "'(1 4 9)"), "(square-list-using-map '(1 2 3))");
ok(scm_equal(scm_eval("(my-map square '(1 2 3))"), "'(1 4 9)"), "(my-map square '(1 2 3))");
ok(scm_equal(scm_eval("(my-append '(1 2) '(3 4))"), "'(1 2 3 4)"), "(my-append '(1 2) '(3 4))");
ok(scm_equal(scm_eval("(my-length '(1 2 3 4))"), 4), "(my-length '(1 2 3 4))");
ok(scm_equal(scm_eval("(count-leaves '(1 2 3 4 5 6))"), 6), "(count-leaves '(1 (2 3) 4 (5 6)))");
ok(scm_equal(scm_eval("(count-leaves '(1 (2 3) 4 (5 6)))"), 6), "(count-leaves '(1 (2 3) 4 (5 6)))");
ok(scm_equal(scm_eval("(equal? 1 (my-car (my-cons 1 2)))"), "#t"), "my-car");
ok(scm_equal(scm_eval("(equal? 2 (my-cdr (my-cons 1 2)))"), "#t"), "my-cdr");


