import tonos_ts4.ts4 as ts4
from casino import Casino


ts4.init('./', verbose = False)

addr = ts4.Address("0:" + "0"*63 + "1")

casino_client = ts4.BaseContract(
    'CasinoClient',
    dict(
        casino=addr
    ),
    keypair=ts4.make_keypair()
)

casino = Casino(
    casino_assurance=4000, 
    minimal_bet=100, 
    owner_wallet=casino_client.address, 
    override_address=addr
)


casino.single_bet(17)


