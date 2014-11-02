from qrcode import *


def generate_character():

	character = { 'name': 'test' }

	return character

def generate_qrcode(data, filename):

	qr = QRCode(version=1, error_correction=ERROR_CORRECT_L)
	qr.add_data()
	qr.make()

	im = qr.make_image()
	im.save()

generate_qrcode("asdjf jasdfkl jlkasdjf lkjaksldfk laksdf kajsdklf j", "filename.png")