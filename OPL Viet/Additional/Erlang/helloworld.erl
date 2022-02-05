% hello world program
% See <https://hostpresto.com/community/tutorials/how-to-install-erlang-on-ubuntu-16-04/>
% to compile:
% 	erlc helloworld.erl
% to run:
% 	erl -noshell -s helloworld start -s init stop
-module(helloworld).
-export([start/0]).
start() ->
io:fwrite("Hello World!\n").
