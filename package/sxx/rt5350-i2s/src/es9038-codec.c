/*
 * es9038.c
 *
 */

#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/soc.h>
#include <linux/of.h>

/*
 * Note this is a simple chip with no configuration interface, sample rate is
 * determined automatically by examining the Master clock and Bit clock ratios
 */
#define ES9038_RATES  (SNDRV_PCM_RATE_44100)


static struct snd_soc_dai_driver es9038_dai[] = {
	{
		.name = "es9038-hifi",
		.playback = {
			.stream_name = "es9038-hifi-playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = ES9038_RATES,
			.formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
		},
	},
};

static struct snd_soc_codec_driver soc_codec_dev_es9038;

static const struct of_device_id es9038_match[] = {
	{ .compatible = "ralink,es9038-hifi" },
	{},
};
MODULE_DEVICE_TABLE(of, es9038_match);

static int es9038_probe(struct platform_device *pdev)
{
	return snd_soc_register_codec(&pdev->dev,
			&soc_codec_dev_es9038, es9038_dai, 1);
}

static int es9038_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

static struct platform_driver es9038_codec_driver = {
	.driver = {
			.name = "es9038-hifi",
			.owner = THIS_MODULE,
            .of_match_table = es9038_match,
	},

	.probe = es9038_probe,
	.remove = es9038_remove,
};

module_platform_driver(es9038_codec_driver);

MODULE_DESCRIPTION("ASoC ES9038 driver");
MODULE_AUTHOR("Derek Quan");
MODULE_LICENSE("GPL");
