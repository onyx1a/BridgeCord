# BridgeCord
[![](https://github.com/onyx1a/BridgeCord/actions/workflows/pip.yml/badge.svg?branch=main)](https://github.com/onyx1a/BridgeCord/actions/workflows/pip.yml)
[![](https://img.shields.io/pypi/v/bridgecord.svg)](https://pypi.org/project/bridgecord/)
[![](https://img.shields.io/github/license/onyx1a/bridgecord.svg)](https://github.com/onyx1a/BridgeCord/blob/main/LICENSE)
[![](https://img.shields.io/pypi/dm/bridgecord)](https://pypi.org/project/bridgecord/)
[![](https://img.shields.io/pypi/pyversions/bridgecord)](https://pypi.org/project/bridgecord/)
```
pip install bridgecord
```
Simple example:
```python
import bridgecord as bc

bridge = bc.Instance()
bridge.init(clientID=CLIENT_ID)
bridge.activity_info.details = "Hello, Python"
bridge.activity_info.state = "In game"
bridge.activity_info.large_image = "dreampyavatar"
bridge.set_timestamps_start(int(time.time()))
bridge.edit_current_activity()
while True:
    bridge.run_callbacks()
```
[![](https://i.imgur.com/RkN3afL.png)]()

`bridge.run_callbacks()` should be [always](https://discord.com/developers/docs/game-sdk/discord#runcallbacks) running.

### Activity:
```python
# Set text, which display on user hovers over large image
bridge.activity_info.large_text = "Large text"
# Set small image, which displayed in right bottom corner
bridge.activity_info.small_image = "dreampy1"
# Set text, which display on user hovers over small image
bridge.activity_info.small_text = "Small text"
```
If you editing any activity info (except timestamps), you should update activity:
```python
bridge.edit_current_activity()
```
### Party info:
```python
bridge.edit_party_info(cur_size=1, max_size=4, id="test", secret="secret", is_private=True)
```
[![](https://i.imgur.com/iKN7uhV.png)]()

This feature allows other users to see the button "Ask to Join", when clicked, will send the user an invitation:

[![](https://i.imgur.com/saoZdEY.png)]()

### Update user profile
You can detect if user change avatar or discord name:
```python
def test_callback() -> None:
    ret, user = bridge.current_user()
    if ret == 0:
        print(user.username)
        print(user.discriminator)
        print(user.avatar_hash)
        print(user.avatar_url)
        print(user.is_bot)
        print(user.id)

bridge.on_current_user_update_connect = test_callback
```
In this example, `current_user()`returned [result code](https://discord.com/developers/docs/game-sdk/discord#data-models-result-enum) and user object.
Output result:
```
onyx1a
3440
c240d87788e9e93464872ac80f047568
https://cdn.discordapp.com/avatars/1052579421875339284/c240d87788e9e93464872ac80f047568.png
False
1052579421875339284
```