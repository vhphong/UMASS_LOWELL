    with Ada.Text_IO, Ada.Integer_Text_IO, Ada.Command_line;
    use  Ada.Text_IO, Ada.Integer_Text_IO, Ada.Command_Line;
-- ----------------------------------------------------------------------------------------- --

-- put two integer inputs on commandline argument to test this code

procedure Test_Combination is
   k, n : Integer;    -- variable for commandline arguments
   function Getn return Integer is        -- funtion for  two commandline arguments
       begin
           k := Integer'Value(Argument(1));    -- converting K to integer
           n := Integer'Value(Argument(2));    -- converting n to integer
           return n;
       end Getn;

      function Getk return Integer is          -- funtion returning K
       begin

           return k;
       end Getk;
   generic
      type Integers is range <>;
   package Combinations is       -- adding combination package
      type Combination is array (Positive range <>) of Integers;

      procedure First (X : in out Combination);
      procedure Next (X : in out Combination);
      procedure Put (X : Combination);

   end Combinations;
-- ----------------------------------------------------------------------------------------- --
   package body Combinations is
      procedure First (X : in out Combination) is
      begin
         X (1) := Integers'First;
         for I in 2..X'Last loop
            X (I) := X (I - 1) + 1;
         end loop;
      end First;
      procedure Next (X : in out Combination) is
      begin
         for I in reverse X'Range loop  -- for loop to loop through the integers
            if X (I) < Integers'Val (Integers'Pos (Integers'Last) - X'Last + I) then
               X (I) := X (I) + 1;
               for J in I + 1..X'Last loop
                  X (J) := X (J - 1) + 1;
               end loop;
               return;
            end if;
         end loop;
         raise Constraint_Error;
      end Next;
      procedure Put (X : Combination) is
      begin
         for I in X'Range loop
            Put (Integers'Image (X (I)));
         end loop;
      end Put;
   end Combinations;
-- ---------------------------------------------------------------------------------------- --
   type Five is new Integer range 1..Getn;         --This is where you specify what N is!!!
   package Fives is new Combinations (Five);
   use Fives;

   X : Combination (1..Getk);    --This is the number of combination that the user wants to have!! This is K
begin
   First (X);
   loop
      Put (X); New_Line;
      Next (X);
   end loop;
exception
   when Constraint_Error =>
      null;
end Test_Combination;
