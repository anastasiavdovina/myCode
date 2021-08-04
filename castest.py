import tonos_ts4.ts4 as ts4
from casino import CasinoClient


ts4.init('./', verbose = False)

addr = ts4.Address("0:" + "0"*63 + "1")

casino_client = ts4.BaseContract(
    'CasinoClient',
    dict(
        casino=addr
    ),
    keypair=ts4.make_keypair()
)

casino = CasinoClient(
    owner_wallet=casino_client.address, 
    override_address=addr
)


casino.single_bet(100, 17)

casino.dozen_bet(100, 1)

casino.color_bet(100, False)

print(casino.balance)
