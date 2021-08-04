import tonos_ts4.ts4 as ts4

class CasinoClient(ts4.BaseContract):
    def __init__(
        self, 
        *,
        owner_wallet: ts4.Address,
        override_address = None,
    ):
        super().__init__(
            'CasinoClient',
            dict(
                casino=owner_wallet
            ),
            override_address=override_address,
            keypair=ts4.make_keypair()
        )
    
    
    def single_bet(self, value, number):
        self.call_method(
            'bet',
            dict(
                value=value,
                number=number,
            ),
            private_key=self.private_key_,
        )
    
    def dozen_bet(self, value, number):
        self.call_method(
            'betDozen',
            dict(
                value=value,
                number=number,
            ),
            private_key=self.private_key_,
        )

    def column_bet(self, value, number):
        self.call_method(
            'betColumn',
            dict(
                value=value,
                number=number,
            ),
            private_key=self.private_key_,
        )

    def great_small_bet(self, value, is_great: bool):
        self.call_method(
            'betGreatSmall',
            dict(
                value=value,
                isGreat=is_great,
            ),
            private_key=self.private_key_,
        )

    def parity_bet(self, value, is_even: bool):
        self.call_method(
            'betParity',
            dict(
                value=value,
                isEven=is_even,
            ),
            private_key=self.private_key_,
        )
    
    def color_bet(self, value, is_red: bool):
        self.call_method(
            'betColor',
            dict(
                value=value,
                isRed=is_red,
            ),
            private_key=self.private_key_,
        )

    def balance(self):
        self.call_getter_raw(
            'balance',
            {},
            0,
        )