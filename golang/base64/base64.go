package base64

import "fmt"

const base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" +
	"abcdefghijklmnopqrstuvwxyz" +
	"0123456789+/"

func encode(input []byte) []byte {
	var ret []byte
	var i, j int
	var charArray3 [3]byte
	var charArray4 [4]byte

	for _, v := range input {
		charArray3[i] = v
		i++
		if i == 3 {
			charArray4[0] = (charArray3[0] & 0xfc) >> 2
			charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4)
			charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6)
			charArray4[3] = charArray3[2] & 0x3f

			for i = 0; i < 4; i++ {
				ret = append(ret, base64Chars[charArray4[i]])
			}
			i = 0
		}
	}

	if i > 0 {
		for j = i; j < 3; j++ {
			charArray3[j] = 0
		}

		charArray4[0] = (charArray3[0] & 0xfc) >> 2
		charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4)
		charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6)

		for j = 0; j < i+1; j++ {
			ret = append(ret, base64Chars[charArray4[j]])
		}

		for ; i < 3; i++ {
			ret = append(ret, '=')
		}

	}

	return ret

}

func main() {
	fmt.Println(base64Chars)
}
