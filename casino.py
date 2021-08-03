import tonos_ts4.ts4 as ts4

class Casino(ts4.BaseContract):
    def __init__(
        self, 
        *,
        casino_assurance: int, 
        minimal_bet: int, 
        owner_wallet: ts4.Address,
        override_address = None,
    ):
        super().__init__(
            'casino',
            dict(
                casinoAssurance=casino_assurance,
                minimalBet=minimal_bet,
                ownerWallet=owner_wallet,
            ),
            override_address=override_address,
            keypair=ts4.make_keypair()
        )
    
    def casino_assurance(self):
        self.call_getter('casino_assurance')

    def minimal_bet(self):
        return self.minimal_bet
    
    def single_bet(self, number):
        self.call_method(
            'singleBet',
            dict(number=number),
            private_key=self.private_key_,
        )
    
    def dozen_bet(self, number):
        self.call_method(
            'dozenBet',
            dict(number=number),
            private_key=self.private_key_,
        )

    def column_bet(self, number):
        self.call_method(
            'columnBet',
            dict(number=number),
            private_key=self.private_key_,
        )

    def great_small_bet(self, is_great: bool):
        self.call_method(
            'greatSmallBet',
            dict(isGreat=is_great),
            private_key=self.private_key_,
        )

    def parity_bet(self, is_even: bool):
        self.call_method(
            'parityBet',
            dict(isEven=is_even),
            private_key=self.private_key_,
        )
    
    def color_bet(self, is_red: bool):
        self.call_method(
            'colorBet',
            dict(isRed=is_red),
            private_key=self.private_key_,
        )