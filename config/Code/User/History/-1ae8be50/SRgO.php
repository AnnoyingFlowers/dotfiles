<html>
    <head>

    </head>
    <body>
        <?php
        $cost = 0;
        $items = $_POST["items[]"];
        $payment = $_POST["payments[]"];
        $username = $_POST["username"];
        foreach($items as $item){
            if(strcmp($item, "four") == 0) {
                $cost += 2.39;
                print("four");
            }
            if(strcmp($item, "eight") == 0) {
                $cost += 4.29;
                print("eight");
            }
            if(strcmp($item, "fourlong") == 0) {
                $cost += 3.95;
                print("fourlong");
            }
            if(strcmp($item, "eightlong") == 0) {
                $cost += 7.49;
                print("eightlong");
            }
        }
        print("The total cost is $cost");
        ?>
    </body>
</html>