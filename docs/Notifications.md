# Notifications

1. Create a Pushbullet account and login both in your mobile phone and on your computer
2. Generate an API Token from your computer
3. Define the API token and the device id

```c
#define PUSHBULLET_API_TOKEN "<API-TOKEN>"
#deine PUSHBULLET_DEVICE_ID "<ID>"
```

You can get the device id by running the following command

```bash
curl -X POST https://api.pushbullet.com/v2/devices -u <API-TOKEN>:
```

